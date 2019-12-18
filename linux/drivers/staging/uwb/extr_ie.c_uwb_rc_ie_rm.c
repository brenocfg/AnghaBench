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
struct uwb_rc {int beaconing; int /*<<< orphan*/  ies_mutex; int /*<<< orphan*/  ies; } ;
typedef  enum uwb_ie { ____Placeholder_uwb_ie } uwb_ie ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_ie_cache_rm (struct uwb_rc*,int) ; 
 int uwb_rc_set_ie (struct uwb_rc*,int /*<<< orphan*/ ) ; 

int uwb_rc_ie_rm(struct uwb_rc *uwb_rc, enum uwb_ie element_id)
{
	int result = 0;

	mutex_lock(&uwb_rc->ies_mutex);

	uwb_rc_ie_cache_rm(uwb_rc, element_id);

	if (uwb_rc->beaconing != -1)
		result = uwb_rc_set_ie(uwb_rc, uwb_rc->ies);

	mutex_unlock(&uwb_rc->ies_mutex);

	return result;
}