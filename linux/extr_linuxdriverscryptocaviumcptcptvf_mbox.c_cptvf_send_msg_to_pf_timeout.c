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
struct cpt_vf {int pf_acked; int pf_nacked; int /*<<< orphan*/  vfid; TYPE_1__* pdev; } ;
struct cpt_mbox {int msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CPT_MBOX_MSG_TIMEOUT ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  cptvf_send_msg_to_pf (struct cpt_vf*,struct cpt_mbox*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cptvf_send_msg_to_pf_timeout(struct cpt_vf *cptvf,
					struct cpt_mbox *mbx)
{
	int timeout = CPT_MBOX_MSG_TIMEOUT;
	int sleep = 10;

	cptvf->pf_acked = false;
	cptvf->pf_nacked = false;
	cptvf_send_msg_to_pf(cptvf, mbx);
	/* Wait for previous message to be acked, timeout 2sec */
	while (!cptvf->pf_acked) {
		if (cptvf->pf_nacked)
			return -EINVAL;
		msleep(sleep);
		if (cptvf->pf_acked)
			break;
		timeout -= sleep;
		if (!timeout) {
			dev_err(&cptvf->pdev->dev, "PF didn't ack to mbox msg %llx from VF%u\n",
				(mbx->msg & 0xFF), cptvf->vfid);
			return -EBUSY;
		}
	}

	return 0;
}