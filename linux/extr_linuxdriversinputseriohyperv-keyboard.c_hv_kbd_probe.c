#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct serio {struct serio* hv_serio; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct serio* port_data; TYPE_2__ id; TYPE_1__ dev; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  lock; struct hv_device* hv_dev; } ;
struct hv_vmbus_device_id {int dummy; } ;
struct hv_kbd_dev {struct hv_kbd_dev* hv_serio; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; struct hv_kbd_dev* port_data; TYPE_2__ id; TYPE_1__ dev; int /*<<< orphan*/  wait_event; int /*<<< orphan*/  lock; struct hv_device* hv_dev; } ;
struct hv_device {int /*<<< orphan*/  channel; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBD_VSC_RECV_RING_BUFFER_SIZE ; 
 int /*<<< orphan*/  KBD_VSC_SEND_RING_BUFFER_SIZE ; 
 int /*<<< orphan*/  SERIO_8042_XL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int hv_kbd_connect_to_vsp (struct hv_device*) ; 
 int /*<<< orphan*/  hv_kbd_on_channel_callback ; 
 int /*<<< orphan*/  hv_kbd_start ; 
 int /*<<< orphan*/  hv_kbd_stop ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct serio*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct serio*) ; 
 struct serio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_register_port (struct serio*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmbus_close (int /*<<< orphan*/ ) ; 
 int vmbus_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hv_device*) ; 

__attribute__((used)) static int hv_kbd_probe(struct hv_device *hv_dev,
			const struct hv_vmbus_device_id *dev_id)
{
	struct hv_kbd_dev *kbd_dev;
	struct serio *hv_serio;
	int error;

	kbd_dev = kzalloc(sizeof(struct hv_kbd_dev), GFP_KERNEL);
	hv_serio = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!kbd_dev || !hv_serio) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	kbd_dev->hv_dev = hv_dev;
	kbd_dev->hv_serio = hv_serio;
	spin_lock_init(&kbd_dev->lock);
	init_completion(&kbd_dev->wait_event);
	hv_set_drvdata(hv_dev, kbd_dev);

	hv_serio->dev.parent  = &hv_dev->device;
	hv_serio->id.type = SERIO_8042_XL;
	hv_serio->port_data = kbd_dev;
	strlcpy(hv_serio->name, dev_name(&hv_dev->device),
		sizeof(hv_serio->name));
	strlcpy(hv_serio->phys, dev_name(&hv_dev->device),
		sizeof(hv_serio->phys));

	hv_serio->start = hv_kbd_start;
	hv_serio->stop = hv_kbd_stop;

	error = vmbus_open(hv_dev->channel,
			   KBD_VSC_SEND_RING_BUFFER_SIZE,
			   KBD_VSC_RECV_RING_BUFFER_SIZE,
			   NULL, 0,
			   hv_kbd_on_channel_callback,
			   hv_dev);
	if (error)
		goto err_free_mem;

	error = hv_kbd_connect_to_vsp(hv_dev);
	if (error)
		goto err_close_vmbus;

	serio_register_port(kbd_dev->hv_serio);

	device_init_wakeup(&hv_dev->device, true);

	return 0;

err_close_vmbus:
	vmbus_close(hv_dev->channel);
err_free_mem:
	kfree(hv_serio);
	kfree(kbd_dev);
	return error;
}