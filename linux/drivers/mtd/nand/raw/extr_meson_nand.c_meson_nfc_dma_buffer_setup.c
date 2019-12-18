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
typedef  int /*<<< orphan*/  u32 ;
struct nand_chip {int dummy; } ;
struct meson_nfc {scalar_t__ reg_base; void* iaddr; void* daddr; int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  GENCMDDADDRH (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GENCMDDADDRL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GENCMDIADDRH (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  GENCMDIADDRL (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  NFC_CMD_ADH ; 
 int /*<<< orphan*/  NFC_CMD_ADL ; 
 int /*<<< orphan*/  NFC_CMD_AIH ; 
 int /*<<< orphan*/  NFC_CMD_AIL ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* dma_map_single (int /*<<< orphan*/ ,void*,int,int) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,int,int) ; 
 struct meson_nfc* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_nfc_dma_buffer_setup(struct nand_chip *nand, void *databuf,
				      int datalen, void *infobuf, int infolen,
				      enum dma_data_direction dir)
{
	struct meson_nfc *nfc = nand_get_controller_data(nand);
	u32 cmd;
	int ret = 0;

	nfc->daddr = dma_map_single(nfc->dev, databuf, datalen, dir);
	ret = dma_mapping_error(nfc->dev, nfc->daddr);
	if (ret) {
		dev_err(nfc->dev, "DMA mapping error\n");
		return ret;
	}
	cmd = GENCMDDADDRL(NFC_CMD_ADL, nfc->daddr);
	writel(cmd, nfc->reg_base + NFC_REG_CMD);

	cmd = GENCMDDADDRH(NFC_CMD_ADH, nfc->daddr);
	writel(cmd, nfc->reg_base + NFC_REG_CMD);

	if (infobuf) {
		nfc->iaddr = dma_map_single(nfc->dev, infobuf, infolen, dir);
		ret = dma_mapping_error(nfc->dev, nfc->iaddr);
		if (ret) {
			dev_err(nfc->dev, "DMA mapping error\n");
			dma_unmap_single(nfc->dev,
					 nfc->daddr, datalen, dir);
			return ret;
		}
		cmd = GENCMDIADDRL(NFC_CMD_AIL, nfc->iaddr);
		writel(cmd, nfc->reg_base + NFC_REG_CMD);

		cmd = GENCMDIADDRH(NFC_CMD_AIH, nfc->iaddr);
		writel(cmd, nfc->reg_base + NFC_REG_CMD);
	}

	return ret;
}