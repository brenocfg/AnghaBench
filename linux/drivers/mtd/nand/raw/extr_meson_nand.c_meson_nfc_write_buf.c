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
typedef  int u32 ;
struct nand_chip {int dummy; } ;
struct meson_nfc {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int NFC_CMD_M2N ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  meson_nfc_dma_buffer_release (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int meson_nfc_dma_buffer_setup (struct nand_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_nfc_drain_cmd (struct meson_nfc*) ; 
 int /*<<< orphan*/  meson_nfc_wait_cmd_finish (struct meson_nfc*,int) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int meson_nfc_write_buf(struct nand_chip *nand, u8 *buf, int len)
{
	struct meson_nfc *nfc = nand_get_controller_data(nand);
	int ret = 0;
	u32 cmd;

	ret = meson_nfc_dma_buffer_setup(nand, buf, len, NULL,
					 0, DMA_TO_DEVICE);
	if (ret)
		return ret;

	cmd = NFC_CMD_M2N | (len & GENMASK(5, 0));
	writel(cmd, nfc->reg_base + NFC_REG_CMD);

	meson_nfc_drain_cmd(nfc);
	meson_nfc_wait_cmd_finish(nfc, 1000);
	meson_nfc_dma_buffer_release(nand, len, 0, DMA_TO_DEVICE);

	return ret;
}