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
typedef  scalar_t__ u16 ;
struct alauda_media_info {unsigned int zonesize; unsigned int zoneshift; scalar_t__** pba_to_lba; } ;

/* Variables and functions */
 scalar_t__ UNDEF ; 

__attribute__((used)) static u16 alauda_find_unused_pba(struct alauda_media_info *info,
	unsigned int zone)
{
	u16 *pba_to_lba = info->pba_to_lba[zone];
	unsigned int i;

	for (i = 0; i < info->zonesize; i++)
		if (pba_to_lba[i] == UNDEF)
			return (zone << info->zoneshift) + i;

	return 0;
}