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
struct sharpsl_nand {scalar_t__ io; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ FLASHCTL ; 
 int FLRYBY ; 
 struct sharpsl_nand* mtd_to_sharpsl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int sharpsl_nand_dev_ready(struct nand_chip *chip)
{
	struct sharpsl_nand *sharpsl = mtd_to_sharpsl(nand_to_mtd(chip));
	return !((readb(sharpsl->io + FLASHCTL) & FLRYBY) == 0);
}