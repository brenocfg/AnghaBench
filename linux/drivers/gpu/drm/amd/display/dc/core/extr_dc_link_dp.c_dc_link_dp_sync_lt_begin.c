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
struct dc_link_training_overrides {int dummy; } ;
struct dc_link_settings {int dummy; } ;
struct dc_link {int sync_lt_in_progress; int /*<<< orphan*/  preferred_link_setting; int /*<<< orphan*/  preferred_training_settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool dc_link_dp_sync_lt_begin(struct dc_link *link)
{
	/* Begin Sync LT. During this time,
	 * DPCD:600h must not be powered down.
	 */
	link->sync_lt_in_progress = true;

	/*Clear any existing preferred settings.*/
	memset(&link->preferred_training_settings, 0,
		sizeof(struct dc_link_training_overrides));
	memset(&link->preferred_link_setting, 0,
		sizeof(struct dc_link_settings));

	return true;
}