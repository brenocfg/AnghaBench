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
struct ScsiReqBlk {int msg_count; TYPE_1__* dcb; int /*<<< orphan*/ * msgin_buf; int /*<<< orphan*/  state; int /*<<< orphan*/ * msgout_buf; } ;
struct AdapterCtlBlk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC395x_ENABLE_MSGOUT ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MESSAGE_REJECT ; 
 int /*<<< orphan*/  SRB_MSGIN ; 
 int /*<<< orphan*/  SRB_MSGOUT ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void msgin_reject(struct AdapterCtlBlk *acb,
		struct ScsiReqBlk *srb)
{
	srb->msgout_buf[0] = MESSAGE_REJECT;
	srb->msg_count = 1;
	DC395x_ENABLE_MSGOUT;
	srb->state &= ~SRB_MSGIN;
	srb->state |= SRB_MSGOUT;
	dprintkl(KERN_INFO, "msgin_reject: 0x%02x <%02i-%i>\n",
		srb->msgin_buf[0],
		srb->dcb->target_id, srb->dcb->target_lun);
}