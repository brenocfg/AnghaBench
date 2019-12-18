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
typedef  int /*<<< orphan*/  u16 ;
struct devx_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_legacy_obj_event_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_legacy_unaffiliated_event_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_valid_events_legacy(int num_events, u16 *event_type_num_list,
				   struct devx_obj *obj)
{
	int i;

	for (i = 0; i < num_events; i++) {
		if (obj) {
			if (!is_legacy_obj_event_num(event_type_num_list[i]))
				return false;
		} else if (!is_legacy_unaffiliated_event_num(
				event_type_num_list[i])) {
			return false;
		}
	}

	return true;
}