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
typedef  int /*<<< orphan*/  u8 ;
struct vivid_dev {int /*<<< orphan*/  osd_jiffies; int /*<<< orphan*/ * osd; } ;
struct cec_msg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * log_addr; } ;
struct cec_adapter {TYPE_1__ log_addrs; } ;

/* Variables and functions */
#define  CEC_MSG_SET_OSD_STRING 131 
 int /*<<< orphan*/  CEC_OP_ABORT_INVALID_OP ; 
#define  CEC_OP_DISP_CTL_CLEAR 130 
#define  CEC_OP_DISP_CTL_DEFAULT 129 
#define  CEC_OP_DISP_CTL_UNTIL_CLEARED 128 
 int ENOMSG ; 
 struct vivid_dev* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_is_sink (struct cec_adapter*) ; 
 int /*<<< orphan*/  cec_msg_destination (struct cec_msg*) ; 
 int /*<<< orphan*/  cec_msg_feature_abort (struct cec_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_msg_init (struct cec_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_msg_initiator (struct cec_msg*) ; 
 scalar_t__ cec_msg_is_broadcast (struct cec_msg*) ; 
 int cec_msg_opcode (struct cec_msg*) ; 
 int /*<<< orphan*/  cec_ops_set_osd_string (struct cec_msg*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cec_transmit_msg (struct cec_adapter*,struct cec_msg*,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int vivid_received(struct cec_adapter *adap, struct cec_msg *msg)
{
	struct vivid_dev *dev = cec_get_drvdata(adap);
	struct cec_msg reply;
	u8 dest = cec_msg_destination(msg);
	u8 disp_ctl;
	char osd[14];

	if (cec_msg_is_broadcast(msg))
		dest = adap->log_addrs.log_addr[0];
	cec_msg_init(&reply, dest, cec_msg_initiator(msg));

	switch (cec_msg_opcode(msg)) {
	case CEC_MSG_SET_OSD_STRING:
		if (!cec_is_sink(adap))
			return -ENOMSG;
		cec_ops_set_osd_string(msg, &disp_ctl, osd);
		switch (disp_ctl) {
		case CEC_OP_DISP_CTL_DEFAULT:
			strscpy(dev->osd, osd, sizeof(dev->osd));
			dev->osd_jiffies = jiffies;
			break;
		case CEC_OP_DISP_CTL_UNTIL_CLEARED:
			strscpy(dev->osd, osd, sizeof(dev->osd));
			dev->osd_jiffies = 0;
			break;
		case CEC_OP_DISP_CTL_CLEAR:
			dev->osd[0] = 0;
			dev->osd_jiffies = 0;
			break;
		default:
			cec_msg_feature_abort(&reply, cec_msg_opcode(msg),
					      CEC_OP_ABORT_INVALID_OP);
			cec_transmit_msg(adap, &reply, false);
			break;
		}
		break;
	default:
		return -ENOMSG;
	}
	return 0;
}