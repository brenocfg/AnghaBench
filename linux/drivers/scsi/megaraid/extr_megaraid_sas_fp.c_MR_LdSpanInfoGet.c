#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct MR_SPAN_BLOCK_INFO {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ldSpanMap; } ;
struct MR_DRV_RAID_MAP_ALL {TYPE_2__ raidMap; } ;
struct TYPE_3__ {struct MR_SPAN_BLOCK_INFO* spanBlock; } ;

/* Variables and functions */

__attribute__((used)) static struct MR_SPAN_BLOCK_INFO *MR_LdSpanInfoGet(u32 ld,
						   struct MR_DRV_RAID_MAP_ALL
						   *map)
{
	return &map->raidMap.ldSpanMap[ld].spanBlock[0];
}