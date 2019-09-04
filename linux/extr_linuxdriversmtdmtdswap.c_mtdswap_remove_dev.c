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
struct mtdswap_dev {int dummy; } ;
struct mtd_blktrans_dev {int dummy; } ;

/* Variables and functions */
 struct mtdswap_dev* MTDSWAP_MBD_TO_MTDSWAP (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  del_mtd_blktrans_dev (struct mtd_blktrans_dev*) ; 
 int /*<<< orphan*/  kfree (struct mtdswap_dev*) ; 
 int /*<<< orphan*/  mtdswap_cleanup (struct mtdswap_dev*) ; 

__attribute__((used)) static void mtdswap_remove_dev(struct mtd_blktrans_dev *dev)
{
	struct mtdswap_dev *d = MTDSWAP_MBD_TO_MTDSWAP(dev);

	del_mtd_blktrans_dev(dev);
	mtdswap_cleanup(d);
	kfree(d);
}