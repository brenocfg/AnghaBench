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
typedef  scalar_t__ u32 ;
struct se_cmd {int /*<<< orphan*/  se_dev; } ;
struct iblock_dev {int /*<<< orphan*/  ibd_bd; int /*<<< orphan*/  ibd_bio_set; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; int /*<<< orphan*/ * bi_end_io; struct se_cmd* bi_private; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ BIO_MAX_PAGES ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 struct iblock_dev* IBLOCK_DEV (int /*<<< orphan*/ ) ; 
 struct bio* bio_alloc_bioset (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int,int) ; 
 int /*<<< orphan*/  iblock_bio_done ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct bio *
iblock_get_bio(struct se_cmd *cmd, sector_t lba, u32 sg_num, int op,
	       int op_flags)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(cmd->se_dev);
	struct bio *bio;

	/*
	 * Only allocate as many vector entries as the bio code allows us to,
	 * we'll loop later on until we have handled the whole request.
	 */
	if (sg_num > BIO_MAX_PAGES)
		sg_num = BIO_MAX_PAGES;

	bio = bio_alloc_bioset(GFP_NOIO, sg_num, &ib_dev->ibd_bio_set);
	if (!bio) {
		pr_err("Unable to allocate memory for bio\n");
		return NULL;
	}

	bio_set_dev(bio, ib_dev->ibd_bd);
	bio->bi_private = cmd;
	bio->bi_end_io = &iblock_bio_done;
	bio->bi_iter.bi_sector = lba;
	bio_set_op_attrs(bio, op, op_flags);

	return bio;
}