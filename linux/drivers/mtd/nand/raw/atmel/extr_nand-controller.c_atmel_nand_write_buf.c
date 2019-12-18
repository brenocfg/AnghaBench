#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int options; int /*<<< orphan*/  controller; } ;
struct atmel_nand_controller {scalar_t__ dmac; } ;
struct atmel_nand {TYPE_2__* activecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  virt; int /*<<< orphan*/  dma; } ;
struct TYPE_4__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int MIN_DMA_LEN ; 
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  atmel_nand_dma_transfer (struct atmel_nand_controller*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16_rep (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  iowrite8_rep (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct atmel_nand* to_atmel_nand (struct nand_chip*) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_addr_valid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void atmel_nand_write_buf(struct nand_chip *chip, const u8 *buf, int len)
{
	struct atmel_nand *nand = to_atmel_nand(chip);
	struct atmel_nand_controller *nc;

	nc = to_nand_controller(chip->controller);

	/*
	 * If the controller supports DMA, the buffer address is DMA-able and
	 * len is long enough to make DMA transfers profitable, let's trigger
	 * a DMA transfer. If it fails, fallback to PIO mode.
	 */
	if (nc->dmac && virt_addr_valid(buf) &&
	    len >= MIN_DMA_LEN &&
	    !atmel_nand_dma_transfer(nc, (void *)buf, nand->activecs->io.dma,
				     len, DMA_TO_DEVICE))
		return;

	if (chip->options & NAND_BUSWIDTH_16)
		iowrite16_rep(nand->activecs->io.virt, buf, len / 2);
	else
		iowrite8_rep(nand->activecs->io.virt, buf, len);
}