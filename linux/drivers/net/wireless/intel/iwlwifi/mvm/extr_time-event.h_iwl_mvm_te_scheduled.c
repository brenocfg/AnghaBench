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
struct iwl_mvm_time_event_data {int /*<<< orphan*/  uid; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
iwl_mvm_te_scheduled(struct iwl_mvm_time_event_data *te_data)
{
	if (!te_data)
		return false;

	return !!te_data->uid;
}