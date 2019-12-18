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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int mxc_nand_write_page (struct nand_chip*,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static int mxc_nand_write_page_ecc(struct nand_chip *chip, const uint8_t *buf,
				   int oob_required, int page)
{
	return mxc_nand_write_page(chip, buf, true, page);
}