#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int level; } ;
struct raid_set {TYPE_1__ md; } ;

/* Variables and functions */

__attribute__((used)) static bool rs_is_raid1(struct raid_set *rs)
{
	return rs->md.level == 1;
}