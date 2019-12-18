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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mxc_nand_host {TYPE_1__* devtype_data; } ;
struct TYPE_2__ {int (* read_page ) (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 int stub1 (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxc_nand_read_oob(struct nand_chip *chip, int page)
{
	struct mxc_nand_host *host = nand_get_controller_data(chip);

	return host->devtype_data->read_page(chip, NULL, chip->oob_poi, 0,
					     page);
}