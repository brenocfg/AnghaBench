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
typedef  int /*<<< orphan*/  uint8_t ;
struct sm_oob {int reserved; } ;
struct sm_ftl {int cis_block; int cis_boffset; scalar_t__ smallpagenand; TYPE_1__* trans; } ;
struct mtd_oob_ops {scalar_t__ oobretlen; scalar_t__ retlen; int /*<<< orphan*/ * datbuf; scalar_t__ len; void* oobbuf; scalar_t__ ooblen; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {int dummy; } ;
struct TYPE_2__ {struct mtd_info* mtd; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 int /*<<< orphan*/  MTD_OPS_RAW ; 
 scalar_t__ SM_OOB_SIZE ; 
 scalar_t__ SM_SECTOR_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dbg (char*,int,int,...) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  mtd_is_bitflip_or_eccerr (int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int mtd_read_oob (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 
 scalar_t__ sm_correct_sector (int /*<<< orphan*/ *,struct sm_oob*) ; 
 int /*<<< orphan*/  sm_mkoffset (struct sm_ftl*,int,int,int) ; 
 scalar_t__ sm_recheck_media (struct sm_ftl*) ; 
 int /*<<< orphan*/  sm_sector_valid (struct sm_oob*) ; 

__attribute__((used)) static int sm_read_sector(struct sm_ftl *ftl,
			  int zone, int block, int boffset,
			  uint8_t *buffer, struct sm_oob *oob)
{
	struct mtd_info *mtd = ftl->trans->mtd;
	struct mtd_oob_ops ops;
	struct sm_oob tmp_oob;
	int ret = -EIO;
	int try = 0;

	/* FTL can contain -1 entries that are by default filled with bits */
	if (block == -1) {
		memset(buffer, 0xFF, SM_SECTOR_SIZE);
		return 0;
	}

	/* User might not need the oob, but we do for data verification */
	if (!oob)
		oob = &tmp_oob;

	ops.mode = ftl->smallpagenand ? MTD_OPS_RAW : MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = SM_OOB_SIZE;
	ops.oobbuf = (void *)oob;
	ops.len = SM_SECTOR_SIZE;
	ops.datbuf = buffer;

again:
	if (try++) {
		/* Avoid infinite recursion on CIS reads, sm_recheck_media
			won't help anyway */
		if (zone == 0 && block == ftl->cis_block && boffset ==
			ftl->cis_boffset)
			return ret;

		/* Test if media is stable */
		if (try == 3 || sm_recheck_media(ftl))
			return ret;
	}

	/* Unfortunately, oob read will _always_ succeed,
		despite card removal..... */
	ret = mtd_read_oob(mtd, sm_mkoffset(ftl, zone, block, boffset), &ops);

	/* Test for unknown errors */
	if (ret != 0 && !mtd_is_bitflip_or_eccerr(ret)) {
		dbg("read of block %d at zone %d, failed due to error (%d)",
			block, zone, ret);
		goto again;
	}

	/* Do a basic test on the oob, to guard against returned garbage */
	if (oob->reserved != 0xFFFFFFFF && !is_power_of_2(~oob->reserved))
		goto again;

	/* This should never happen, unless there is a bug in the mtd driver */
	WARN_ON(ops.oobretlen != SM_OOB_SIZE);
	WARN_ON(buffer && ops.retlen != SM_SECTOR_SIZE);

	if (!buffer)
		return 0;

	/* Test if sector marked as bad */
	if (!sm_sector_valid(oob)) {
		dbg("read of block %d at zone %d, failed because it is marked"
			" as bad" , block, zone);
		goto again;
	}

	/* Test ECC*/
	if (mtd_is_eccerr(ret) ||
		(ftl->smallpagenand && sm_correct_sector(buffer, oob))) {

		dbg("read of block %d at zone %d, failed due to ECC error",
			block, zone);
		goto again;
	}

	return 0;
}