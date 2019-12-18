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
struct i40e_pf {int num_alloc_vfs; int /*<<< orphan*/ * vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_vc_notify_vf_link_state (int /*<<< orphan*/ *) ; 

void i40e_vc_notify_link_state(struct i40e_pf *pf)
{
	int i;

	for (i = 0; i < pf->num_alloc_vfs; i++)
		i40e_vc_notify_vf_link_state(&pf->vf[i]);
}