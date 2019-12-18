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
struct i40e_new_mac_filter {int /*<<< orphan*/  state; } ;
struct i40e_aqc_add_macvlan_element_data {scalar_t__ match_method; } ;

/* Variables and functions */
 scalar_t__ I40E_AQC_MM_ERR_NO_RES ; 
 int /*<<< orphan*/  I40E_FILTER_ACTIVE ; 
 int /*<<< orphan*/  I40E_FILTER_FAILED ; 
 struct i40e_new_mac_filter* i40e_next_filter (struct i40e_new_mac_filter*) ; 

__attribute__((used)) static int
i40e_update_filter_state(int count,
			 struct i40e_aqc_add_macvlan_element_data *add_list,
			 struct i40e_new_mac_filter *add_head)
{
	int retval = 0;
	int i;

	for (i = 0; i < count; i++) {
		/* Always check status of each filter. We don't need to check
		 * the firmware return status because we pre-set the filter
		 * status to I40E_AQC_MM_ERR_NO_RES when sending the filter
		 * request to the adminq. Thus, if it no longer matches then
		 * we know the filter is active.
		 */
		if (add_list[i].match_method == I40E_AQC_MM_ERR_NO_RES) {
			add_head->state = I40E_FILTER_FAILED;
		} else {
			add_head->state = I40E_FILTER_ACTIVE;
			retval++;
		}

		add_head = i40e_next_filter(add_head);
		if (!add_head)
			break;
	}

	return retval;
}