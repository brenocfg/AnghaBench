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
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct i40iw_sge {int /*<<< orphan*/  stag; int /*<<< orphan*/  len; int /*<<< orphan*/  tag_off; } ;

/* Variables and functions */
 unsigned int I40IW_MAX_WQ_FRAGMENT_COUNT ; 

__attribute__((used)) static void i40iw_copy_sg_list(struct i40iw_sge *sg_list, struct ib_sge *sgl, int num_sges)
{
	unsigned int i;

	for (i = 0; (i < num_sges) && (i < I40IW_MAX_WQ_FRAGMENT_COUNT); i++) {
		sg_list[i].tag_off = sgl[i].addr;
		sg_list[i].len = sgl[i].length;
		sg_list[i].stag = sgl[i].lkey;
	}
}