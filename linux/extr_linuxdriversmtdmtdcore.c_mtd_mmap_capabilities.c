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
struct mtd_info {int type; } ;

/* Variables and functions */
#define  MTD_RAM 129 
#define  MTD_ROM 128 
 int NOMMU_MAP_COPY ; 
 int NOMMU_MAP_DIRECT ; 
 int NOMMU_MAP_EXEC ; 
 int NOMMU_MAP_READ ; 
 int NOMMU_MAP_WRITE ; 

unsigned mtd_mmap_capabilities(struct mtd_info *mtd)
{
	switch (mtd->type) {
	case MTD_RAM:
		return NOMMU_MAP_COPY | NOMMU_MAP_DIRECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_READ | NOMMU_MAP_WRITE;
	case MTD_ROM:
		return NOMMU_MAP_COPY | NOMMU_MAP_DIRECT | NOMMU_MAP_EXEC |
			NOMMU_MAP_READ;
	default:
		return NOMMU_MAP_COPY;
	}
}