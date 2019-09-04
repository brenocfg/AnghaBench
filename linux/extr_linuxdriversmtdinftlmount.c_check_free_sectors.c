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
typedef  int /*<<< orphan*/  u8 ;
struct mtd_info {int oobsize; } ;
struct TYPE_2__ {struct mtd_info* mtd; } ;
struct INFTLrecord {TYPE_1__ mbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SECTORSIZE ; 
 scalar_t__ inftl_read_oob (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmpb (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ mtd_read (struct mtd_info*,unsigned int,int,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_free_sectors(struct INFTLrecord *inftl, unsigned int address,
	int len, int check_oob)
{
	struct mtd_info *mtd = inftl->mbd.mtd;
	size_t retlen;
	int i, ret;
	u8 *buf;

	buf = kmalloc(SECTORSIZE + mtd->oobsize, GFP_KERNEL);
	if (!buf)
		return -1;

	ret = -1;
	for (i = 0; i < len; i += SECTORSIZE) {
		if (mtd_read(mtd, address, SECTORSIZE, &retlen, buf))
			goto out;
		if (memcmpb(buf, 0xff, SECTORSIZE) != 0)
			goto out;

		if (check_oob) {
			if(inftl_read_oob(mtd, address, mtd->oobsize,
					  &retlen, &buf[SECTORSIZE]) < 0)
				goto out;
			if (memcmpb(buf + SECTORSIZE, 0xff, mtd->oobsize) != 0)
				goto out;
		}
		address += SECTORSIZE;
	}

	ret = 0;

out:
	kfree(buf);
	return ret;
}