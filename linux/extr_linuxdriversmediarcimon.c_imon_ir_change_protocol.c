#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct rc_dev {int allowed_protocols; struct imon_context* priv; } ;
struct imon_context {int rc_proto; int pad_mouse; int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_tx_buf; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ir_proto_packet ;

/* Variables and functions */
 int RC_PROTO_BIT_IMON ; 
 int RC_PROTO_BIT_RC6_MCE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char**,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad_stabilize ; 
 int send_packet (struct imon_context*) ; 

__attribute__((used)) static int imon_ir_change_protocol(struct rc_dev *rc, u64 *rc_proto)
{
	int retval;
	struct imon_context *ictx = rc->priv;
	struct device *dev = ictx->dev;
	bool unlock = false;
	unsigned char ir_proto_packet[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x86 };

	if (*rc_proto && !(*rc_proto & rc->allowed_protocols))
		dev_warn(dev, "Looks like you're trying to use an IR protocol this device does not support\n");

	if (*rc_proto & RC_PROTO_BIT_RC6_MCE) {
		dev_dbg(dev, "Configuring IR receiver for MCE protocol\n");
		ir_proto_packet[0] = 0x01;
		*rc_proto = RC_PROTO_BIT_RC6_MCE;
	} else if (*rc_proto & RC_PROTO_BIT_IMON) {
		dev_dbg(dev, "Configuring IR receiver for iMON protocol\n");
		if (!pad_stabilize)
			dev_dbg(dev, "PAD stabilize functionality disabled\n");
		/* ir_proto_packet[0] = 0x00; // already the default */
		*rc_proto = RC_PROTO_BIT_IMON;
	} else {
		dev_warn(dev, "Unsupported IR protocol specified, overriding to iMON IR protocol\n");
		if (!pad_stabilize)
			dev_dbg(dev, "PAD stabilize functionality disabled\n");
		/* ir_proto_packet[0] = 0x00; // already the default */
		*rc_proto = RC_PROTO_BIT_IMON;
	}

	memcpy(ictx->usb_tx_buf, &ir_proto_packet, sizeof(ir_proto_packet));

	if (!mutex_is_locked(&ictx->lock)) {
		unlock = true;
		mutex_lock(&ictx->lock);
	}

	retval = send_packet(ictx);
	if (retval)
		goto out;

	ictx->rc_proto = *rc_proto;
	ictx->pad_mouse = false;

out:
	if (unlock)
		mutex_unlock(&ictx->lock);

	return retval;
}