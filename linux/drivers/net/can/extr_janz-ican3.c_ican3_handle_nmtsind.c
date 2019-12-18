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
typedef  scalar_t__ u16 ;
struct ican3_msg {int* data; int /*<<< orphan*/  len; } ;
struct ican3_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
#define  NE_LOCAL_OCCURRED 131 
#define  NE_LOCAL_RESOLVED 130 
#define  NE_REMOTE_OCCURRED 129 
#define  NE_REMOTE_RESOLVED 128 
 scalar_t__ NMTS_SLAVE_EVENT_IND ; 
 scalar_t__ NMTS_SLAVE_STATE_IND ; 
 int /*<<< orphan*/  ican3_handle_cevtind (struct ican3_dev*,struct ican3_msg*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void ican3_handle_nmtsind(struct ican3_dev *mod, struct ican3_msg *msg)
{
	u16 subspec;

	subspec = msg->data[0] + msg->data[1] * 0x100;
	if (subspec == NMTS_SLAVE_EVENT_IND) {
		switch (msg->data[2]) {
		case NE_LOCAL_OCCURRED:
		case NE_LOCAL_RESOLVED:
			/* now follows the same message as Raw ICANOS CEVTIND
			 * shift the data at the same place and call this method
			 */
			le16_add_cpu(&msg->len, -3);
			memmove(msg->data, msg->data + 3, le16_to_cpu(msg->len));
			ican3_handle_cevtind(mod, msg);
			break;
		case NE_REMOTE_OCCURRED:
		case NE_REMOTE_RESOLVED:
			/* should not occurre, ignore */
			break;
		default:
			netdev_warn(mod->ndev, "unknown NMTS event indication %x\n",
				    msg->data[2]);
			break;
		}
	} else if (subspec == NMTS_SLAVE_STATE_IND) {
		/* ignore state indications */
	} else {
		netdev_warn(mod->ndev, "unhandled NMTS indication %x\n",
			    subspec);
		return;
	}
}