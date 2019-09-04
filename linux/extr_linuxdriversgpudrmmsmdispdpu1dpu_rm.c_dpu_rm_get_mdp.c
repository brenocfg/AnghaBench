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
struct dpu_rm {struct dpu_hw_mdp* hw_mdp; } ;
struct dpu_hw_mdp {int dummy; } ;

/* Variables and functions */

struct dpu_hw_mdp *dpu_rm_get_mdp(struct dpu_rm *rm)
{
	return rm->hw_mdp;
}