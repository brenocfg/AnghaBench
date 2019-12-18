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
struct meson_nfc_nand_chip {int /*<<< orphan*/  data_buf; int /*<<< orphan*/  info_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct meson_nfc_nand_chip* to_meson_nand (struct nand_chip*) ; 

__attribute__((used)) static void meson_nfc_free_buffer(struct nand_chip *nand)
{
	struct meson_nfc_nand_chip *meson_chip = to_meson_nand(nand);

	kfree(meson_chip->info_buf);
	kfree(meson_chip->data_buf);
}