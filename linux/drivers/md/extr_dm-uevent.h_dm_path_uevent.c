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
struct dm_target {int dummy; } ;
typedef  enum dm_uevent_type { ____Placeholder_dm_uevent_type } dm_uevent_type ;

/* Variables and functions */

__attribute__((used)) static inline void dm_path_uevent(enum dm_uevent_type event_type,
				  struct dm_target *ti, const char *path,
				  unsigned nr_valid_paths)
{
}