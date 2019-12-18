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
struct nand_chip {int dummy; } ;
struct hinfc_host {int chipselect; } ;

/* Variables and functions */
 struct hinfc_host* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void hisi_nfc_select_chip(struct nand_chip *chip, int chipselect)
{
	struct hinfc_host *host = nand_get_controller_data(chip);

	if (chipselect < 0)
		return;

	host->chipselect = chipselect;
}