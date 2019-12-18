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
struct sm_ftl {int zone_count; int zone_size; int block_size; } ;
typedef  int loff_t ;

/* Variables and functions */
 int SM_MAX_ZONE_SIZE ; 
 int SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static loff_t sm_mkoffset(struct sm_ftl *ftl, int zone, int block, int boffset)
{
	WARN_ON(boffset & (SM_SECTOR_SIZE - 1));
	WARN_ON(zone < 0 || zone >= ftl->zone_count);
	WARN_ON(block >= ftl->zone_size);
	WARN_ON(boffset >= ftl->block_size);

	if (block == -1)
		return -1;

	return (zone * SM_MAX_ZONE_SIZE + block) * ftl->block_size + boffset;
}