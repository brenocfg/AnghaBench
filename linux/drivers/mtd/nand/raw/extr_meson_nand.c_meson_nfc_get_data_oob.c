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
struct TYPE_2__ {int bytes; int steps; int size; } ;
struct nand_chip {TYPE_1__ ecc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * meson_nfc_data_ptr (struct nand_chip*,int) ; 
 int /*<<< orphan*/ * meson_nfc_oob_ptr (struct nand_chip*,int) ; 

__attribute__((used)) static void meson_nfc_get_data_oob(struct nand_chip *nand,
				   u8 *buf, u8 *oobbuf)
{
	int i, oob_len = 0;
	u8 *dsrc, *osrc;

	oob_len = nand->ecc.bytes + 2;
	for (i = 0; i < nand->ecc.steps; i++) {
		if (buf) {
			dsrc = meson_nfc_data_ptr(nand, i);
			memcpy(buf, dsrc, nand->ecc.size);
			buf += nand->ecc.size;
		}
		osrc = meson_nfc_oob_ptr(nand, i);
		memcpy(oobbuf, osrc, oob_len);
		oobbuf += oob_len;
	}
}