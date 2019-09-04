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
struct ssfdcr_record {int /*<<< orphan*/  logic_block_map; } ;
struct mtd_blktrans_dev {int /*<<< orphan*/  devnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssfdcr_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct ssfdcr_record *ssfdc = (struct ssfdcr_record *)dev;

	pr_debug("SSFDC_RO: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);
	kfree(ssfdc->logic_block_map);
}