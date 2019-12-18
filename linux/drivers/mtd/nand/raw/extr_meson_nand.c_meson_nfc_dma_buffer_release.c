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
struct meson_nfc {int /*<<< orphan*/  iaddr; int /*<<< orphan*/  dev; int /*<<< orphan*/  daddr; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static void meson_nfc_dma_buffer_release(struct nand_chip *nand,
					 int infolen, int datalen,
					 enum dma_data_direction dir)
{
	struct meson_nfc *nfc = nand_get_controller_data(nand);

	dma_unmap_single(nfc->dev, nfc->daddr, datalen, dir);
	if (infolen)
		dma_unmap_single(nfc->dev, nfc->iaddr, infolen, dir);
}