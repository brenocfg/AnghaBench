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
struct TYPE_2__ {int (* read_page ) (struct nand_chip*,int /*<<< orphan*/ *,int,int) ;} ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * nand_get_data_buf (struct nand_chip*) ; 
 int stub1 (struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_oob(struct nand_chip *nand, int page)
{
	u8 *buf = nand_get_data_buf(nand);

	return nand->ecc.read_page(nand, buf, 1, page);
}