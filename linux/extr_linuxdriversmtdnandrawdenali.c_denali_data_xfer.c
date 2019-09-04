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
struct denali_nand_info {scalar_t__ dma_avail; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ ECC_ENABLE ; 
 int /*<<< orphan*/  ECC_ENABLE__FLAG ; 
 scalar_t__ TRANSFER_SPARE_REG ; 
 int /*<<< orphan*/  TRANSFER_SPARE_REG__FLAG ; 
 int denali_dma_xfer (struct denali_nand_info*,void*,size_t,int,int,int) ; 
 int denali_pio_xfer (struct denali_nand_info*,void*,size_t,int,int,int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int denali_data_xfer(struct denali_nand_info *denali, void *buf,
			    size_t size, int page, int raw, int write)
{
	iowrite32(raw ? 0 : ECC_ENABLE__FLAG, denali->reg + ECC_ENABLE);
	iowrite32(raw ? TRANSFER_SPARE_REG__FLAG : 0,
		  denali->reg + TRANSFER_SPARE_REG);

	if (denali->dma_avail)
		return denali_dma_xfer(denali, buf, size, page, raw, write);
	else
		return denali_pio_xfer(denali, buf, size, page, raw, write);
}