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
typedef  void* u32 ;
struct i40e_pf {void* max_bw; void* min_bw; int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_read_bw_from_alt_ram (int /*<<< orphan*/ *,void**,void**,int*,int*) ; 

i40e_status i40e_get_partition_bw_setting(struct i40e_pf *pf)
{
	i40e_status status;
	bool min_valid, max_valid;
	u32 max_bw, min_bw;

	status = i40e_read_bw_from_alt_ram(&pf->hw, &max_bw, &min_bw,
					   &min_valid, &max_valid);

	if (!status) {
		if (min_valid)
			pf->min_bw = min_bw;
		if (max_valid)
			pf->max_bw = max_bw;
	}

	return status;
}