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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_nfc_get_data_oob (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int meson_nfc_read_page_sub (struct nand_chip*,int,int) ; 

__attribute__((used)) static int meson_nfc_read_page_raw(struct nand_chip *nand, u8 *buf,
				   int oob_required, int page)
{
	u8 *oob_buf = nand->oob_poi;
	int ret;

	ret = meson_nfc_read_page_sub(nand, page, 1);
	if (ret)
		return ret;

	meson_nfc_get_data_oob(nand, buf, oob_buf);

	return 0;
}