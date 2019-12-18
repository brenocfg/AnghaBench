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
struct r852_device {int dummy; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CARD_STA ; 
 int R852_CARD_STA_BUSY ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct r852_device* r852_get_dev (int /*<<< orphan*/ ) ; 
 int r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r852_ready(struct nand_chip *chip)
{
	struct r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	return !(r852_read_reg(dev, R852_CARD_STA) & R852_CARD_STA_BUSY);
}