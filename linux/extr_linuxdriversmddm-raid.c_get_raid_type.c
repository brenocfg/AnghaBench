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
struct raid_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct raid_type*) ; 
 struct raid_type* raid_types ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct raid_type *get_raid_type(const char *name)
{
	struct raid_type *rtp = raid_types + ARRAY_SIZE(raid_types);

	while (rtp-- > raid_types)
		if (!strcasecmp(rtp->name, name))
			return rtp;

	return NULL;
}