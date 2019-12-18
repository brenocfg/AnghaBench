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
struct fmdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_AF_JUMP_SET_AF_FREQ_IDX ; 
 int /*<<< orphan*/  fm_irq_common_cmd_resp_helper (struct fmdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm_irq_handle_set_pimask_resp(struct fmdev *fmdev)
{
	fm_irq_common_cmd_resp_helper(fmdev, FM_AF_JUMP_SET_AF_FREQ_IDX);
}