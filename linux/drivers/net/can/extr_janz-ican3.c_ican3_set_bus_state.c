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
typedef  int u8 ;
struct ican3_msg {int* data; void* len; int /*<<< orphan*/  spec; } ;
struct can_bittiming {int brp; int sjw; int prop_seg; int phase_seg1; int phase_seg2; } ;
struct TYPE_2__ {int ctrlmode; struct can_bittiming bittiming; } ;
struct ican3_dev {scalar_t__ fwtype; TYPE_1__ can; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int CAN_CTRLMODE_3_SAMPLES ; 
 int ENOTSUPP ; 
 scalar_t__ ICAN3_FWTYPE_CAL_CANOPEN ; 
 scalar_t__ ICAN3_FWTYPE_ICANOS ; 
 int LMTS_BUSOFF_REQ ; 
 int LMTS_BUSON_REQ ; 
 int /*<<< orphan*/  MSG_CBTRREQ ; 
 int /*<<< orphan*/  MSG_COFFREQ ; 
 int /*<<< orphan*/  MSG_CONREQ ; 
 int /*<<< orphan*/  MSG_LMTS ; 
 int /*<<< orphan*/  MSG_NMTS ; 
 int NMTS_CREATE_NODE_REQ ; 
 void* cpu_to_le16 (int) ; 
 int ican3_send_msg (struct ican3_dev*,struct ican3_msg*) ; 
 int /*<<< orphan*/  memset (struct ican3_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 

__attribute__((used)) static int ican3_set_bus_state(struct ican3_dev *mod, bool on)
{
	struct can_bittiming *bt = &mod->can.bittiming;
	struct ican3_msg msg;
	u8 btr0, btr1;
	int res;

	/* This algorithm was stolen from drivers/net/can/sja1000/sja1000.c      */
	/* The bittiming register command for the ICAN3 just sets the bit timing */
	/* registers on the SJA1000 chip directly                                */
	btr0 = ((bt->brp - 1) & 0x3f) | (((bt->sjw - 1) & 0x3) << 6);
	btr1 = ((bt->prop_seg + bt->phase_seg1 - 1) & 0xf) |
		(((bt->phase_seg2 - 1) & 0x7) << 4);
	if (mod->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES)
		btr1 |= 0x80;

	if (mod->fwtype == ICAN3_FWTYPE_ICANOS) {
		if (on) {
			/* set bittiming */
			memset(&msg, 0, sizeof(msg));
			msg.spec = MSG_CBTRREQ;
			msg.len = cpu_to_le16(4);
			msg.data[0] = 0x00;
			msg.data[1] = 0x00;
			msg.data[2] = btr0;
			msg.data[3] = btr1;

			res = ican3_send_msg(mod, &msg);
			if (res)
				return res;
		}

		/* can-on/off request */
		memset(&msg, 0, sizeof(msg));
		msg.spec = on ? MSG_CONREQ : MSG_COFFREQ;
		msg.len = cpu_to_le16(0);

		return ican3_send_msg(mod, &msg);

	} else if (mod->fwtype == ICAN3_FWTYPE_CAL_CANOPEN) {
		/* bittiming + can-on/off request */
		memset(&msg, 0, sizeof(msg));
		msg.spec = MSG_LMTS;
		if (on) {
			msg.len = cpu_to_le16(4);
			msg.data[0] = LMTS_BUSON_REQ;
			msg.data[1] = 0;
			msg.data[2] = btr0;
			msg.data[3] = btr1;
		} else {
			msg.len = cpu_to_le16(2);
			msg.data[0] = LMTS_BUSOFF_REQ;
			msg.data[1] = 0;
		}
		res = ican3_send_msg(mod, &msg);
		if (res)
			return res;

		if (on) {
			/* create NMT Slave Node for error processing
			 *   class 2 (with error capability, see CiA/DS203-1)
			 *   id    1
			 *   name  locnod1 (must be exactly 7 bytes)
			 */
			memset(&msg, 0, sizeof(msg));
			msg.spec = MSG_NMTS;
			msg.len = cpu_to_le16(11);
			msg.data[0] = NMTS_CREATE_NODE_REQ;
			msg.data[1] = 0;
			msg.data[2] = 2;                 /* node class */
			msg.data[3] = 1;                 /* node id */
			strcpy(msg.data + 4, "locnod1"); /* node name  */
			return ican3_send_msg(mod, &msg);
		}
		return 0;
	}
	return -ENOTSUPP;
}