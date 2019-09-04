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
typedef  size_t u_long ;
struct partition {int reserved_block; size_t sector_count; size_t* sector_map; } ;
struct mtd_blktrans_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 int SECTOR_SIZE ; 
 int do_writesect (struct mtd_blktrans_dev*,size_t,char*,size_t*) ; 
 int mark_sector_deleted (struct partition*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 

__attribute__((used)) static int rfd_ftl_writesect(struct mtd_blktrans_dev *dev, u_long sector, char *buf)
{
	struct partition *part = (struct partition*)dev;
	u_long old_addr;
	int i;
	int rc = 0;

	pr_debug("rfd_ftl_writesect(sector=0x%lx)\n", sector);

	if (part->reserved_block == -1) {
		rc = -EACCES;
		goto err;
	}

	if (sector >= part->sector_count) {
		rc = -EIO;
		goto err;
	}

	old_addr = part->sector_map[sector];

	for (i=0; i<SECTOR_SIZE; i++) {
		if (!buf[i])
			continue;

		rc = do_writesect(dev, sector, buf, &old_addr);
		if (rc)
			goto err;
		break;
	}

	if (i == SECTOR_SIZE)
		part->sector_map[sector] = -1;

	if (old_addr != -1)
		rc = mark_sector_deleted(part, old_addr);

err:
	return rc;
}