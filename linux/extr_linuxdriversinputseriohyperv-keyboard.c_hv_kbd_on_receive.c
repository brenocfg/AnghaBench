#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct synth_kbd_protocol_response {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct synth_kbd_msg {TYPE_1__ header; } ;
struct synth_kbd_keystroke {int /*<<< orphan*/  make_code; int /*<<< orphan*/  info; } ;
struct hv_kbd_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  hv_serio; int /*<<< orphan*/  started; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  protocol_resp; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int IS_BREAK ; 
 int IS_E0 ; 
 int IS_E1 ; 
#define  SYNTH_KBD_EVENT 129 
#define  SYNTH_KBD_PROTOCOL_RESPONSE 128 
 int /*<<< orphan*/  XTKBD_EMUL0 ; 
 int /*<<< orphan*/  XTKBD_EMUL1 ; 
 int /*<<< orphan*/  XTKBD_RELEASE ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hv_kbd_dev* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct synth_kbd_msg*,int) ; 
 int /*<<< orphan*/  pm_wakeup_hard_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hv_kbd_on_receive(struct hv_device *hv_dev,
			      struct synth_kbd_msg *msg, u32 msg_length)
{
	struct hv_kbd_dev *kbd_dev = hv_get_drvdata(hv_dev);
	struct synth_kbd_keystroke *ks_msg;
	unsigned long flags;
	u32 msg_type = __le32_to_cpu(msg->header.type);
	u32 info;
	u16 scan_code;

	switch (msg_type) {
	case SYNTH_KBD_PROTOCOL_RESPONSE:
		/*
		 * Validate the information provided by the host.
		 * If the host is giving us a bogus packet,
		 * drop the packet (hoping the problem
		 * goes away).
		 */
		if (msg_length < sizeof(struct synth_kbd_protocol_response)) {
			dev_err(&hv_dev->device,
				"Illegal protocol response packet (len: %d)\n",
				msg_length);
			break;
		}

		memcpy(&kbd_dev->protocol_resp, msg,
			sizeof(struct synth_kbd_protocol_response));
		complete(&kbd_dev->wait_event);
		break;

	case SYNTH_KBD_EVENT:
		/*
		 * Validate the information provided by the host.
		 * If the host is giving us a bogus packet,
		 * drop the packet (hoping the problem
		 * goes away).
		 */
		if (msg_length < sizeof(struct  synth_kbd_keystroke)) {
			dev_err(&hv_dev->device,
				"Illegal keyboard event packet (len: %d)\n",
				msg_length);
			break;
		}

		ks_msg = (struct synth_kbd_keystroke *)msg;
		info = __le32_to_cpu(ks_msg->info);

		/*
		 * Inject the information through the serio interrupt.
		 */
		spin_lock_irqsave(&kbd_dev->lock, flags);
		if (kbd_dev->started) {
			if (info & IS_E0)
				serio_interrupt(kbd_dev->hv_serio,
						XTKBD_EMUL0, 0);
			if (info & IS_E1)
				serio_interrupt(kbd_dev->hv_serio,
						XTKBD_EMUL1, 0);
			scan_code = __le16_to_cpu(ks_msg->make_code);
			if (info & IS_BREAK)
				scan_code |= XTKBD_RELEASE;

			serio_interrupt(kbd_dev->hv_serio, scan_code, 0);
		}
		spin_unlock_irqrestore(&kbd_dev->lock, flags);

		/*
		 * Only trigger a wakeup on key down, otherwise
		 * "echo freeze > /sys/power/state" can't really enter the
		 * state because the Enter-UP can trigger a wakeup at once.
		 */
		if (!(info & IS_BREAK))
			pm_wakeup_hard_event(&hv_dev->device);

		break;

	default:
		dev_err(&hv_dev->device,
			"unhandled message type %d\n", msg_type);
	}
}