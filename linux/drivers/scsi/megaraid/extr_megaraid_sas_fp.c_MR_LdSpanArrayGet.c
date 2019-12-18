#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {TYPE_3__* ldSpanMap; } ;
struct MR_DRV_RAID_MAP_ALL {TYPE_4__ raidMap; } ;
struct TYPE_7__ {TYPE_2__* spanBlock; } ;
struct TYPE_5__ {int /*<<< orphan*/  arrayRef; } ;
struct TYPE_6__ {TYPE_1__ span; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

u16 MR_LdSpanArrayGet(u32 ld, u32 span, struct MR_DRV_RAID_MAP_ALL *map)
{
	return le16_to_cpu(map->raidMap.ldSpanMap[ld].spanBlock[span].span.arrayRef);
}