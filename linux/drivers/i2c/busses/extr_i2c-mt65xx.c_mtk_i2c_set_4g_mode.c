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
typedef  int dma_addr_t ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  I2C_DMA_4G_MODE ; 
 int /*<<< orphan*/  I2C_DMA_CLR_FLAG ; 

__attribute__((used)) static inline u32 mtk_i2c_set_4g_mode(dma_addr_t addr)
{
	return (addr & BIT_ULL(32)) ? I2C_DMA_4G_MODE : I2C_DMA_CLR_FLAG;
}