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
struct spinand_device {int /*<<< orphan*/  scratchbuf; int /*<<< orphan*/  databuf; } ;
struct nand_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanddev_cleanup (struct nand_device*) ; 
 int /*<<< orphan*/  spinand_manufacturer_cleanup (struct spinand_device*) ; 
 struct nand_device* spinand_to_nand (struct spinand_device*) ; 

__attribute__((used)) static void spinand_cleanup(struct spinand_device *spinand)
{
	struct nand_device *nand = spinand_to_nand(spinand);

	nanddev_cleanup(nand);
	spinand_manufacturer_cleanup(spinand);
	kfree(spinand->databuf);
	kfree(spinand->scratchbuf);
}