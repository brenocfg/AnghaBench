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
typedef  int u32 ;
struct beiscsi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int POST_ERROR_BIT ; 
 int POST_STAGE_ARMFW_RDY ; 
 int POST_STAGE_MASK ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,int) ; 
 int beiscsi_get_post_stage (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int beiscsi_check_fw_rdy(struct beiscsi_hba *phba)
{
	u32 loop, post, rdy = 0;

	loop = 1000;
	while (loop--) {
		post = beiscsi_get_post_stage(phba);
		if (post & POST_ERROR_BIT)
			break;
		if ((post & POST_STAGE_MASK) == POST_STAGE_ARMFW_RDY) {
			rdy = 1;
			break;
		}
		msleep(60);
	}

	if (!rdy) {
		__beiscsi_log(phba, KERN_ERR,
			      "BC_%d : FW not ready 0x%x\n", post);
	}

	return rdy;
}