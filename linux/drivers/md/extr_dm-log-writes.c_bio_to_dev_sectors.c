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
struct log_writes_c {int sectorshift; } ;
typedef  int sector_t ;

/* Variables and functions */
 int SECTOR_SHIFT ; 

__attribute__((used)) static inline sector_t bio_to_dev_sectors(struct log_writes_c *lc,
					  sector_t sectors)
{
	return sectors >> (lc->sectorshift - SECTOR_SHIFT);
}