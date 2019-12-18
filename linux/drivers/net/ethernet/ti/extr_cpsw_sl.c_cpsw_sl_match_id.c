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
struct cpsw_sl_dev_id {scalar_t__ device_id; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct cpsw_sl_dev_id *cpsw_sl_match_id(
		const struct cpsw_sl_dev_id *id,
		const char *device_id)
{
	if (!id || !device_id)
		return NULL;

	while (id->device_id) {
		if (strcmp(device_id, id->device_id) == 0)
			return id;
		id++;
	}
	return NULL;
}