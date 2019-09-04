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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GDROM_DMA_ACCESS_CTRL_REG ; 
 int /*<<< orphan*/  GDROM_DMA_WAIT_REG ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 int /*<<< orphan*/  GDROM_INTSEC_REG ; 
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdrom_wait_busy_sleeps () ; 
 int /*<<< orphan*/  gdrom_wait_clrbusy () ; 

__attribute__((used)) static int gdrom_init_dma_mode(void)
{
	__raw_writeb(0x13, GDROM_ERROR_REG);
	__raw_writeb(0x22, GDROM_INTSEC_REG);
	if (!gdrom_wait_clrbusy())
		return -EBUSY;
	__raw_writeb(0xEF, GDROM_STATUSCOMMAND_REG);
	if (!gdrom_wait_busy_sleeps())
		return -EBUSY;
	/* Memory protection setting for GDROM DMA
	* Bits 31 - 16 security: 0x8843
	* Bits 15 and 7 reserved (0)
	* Bits 14 - 8 start of transfer range in 1 MB blocks OR'ed with 0x80
	* Bits 6 - 0 end of transfer range in 1 MB blocks OR'ed with 0x80
	* (0x40 | 0x80) = start range at 0x0C000000
	* (0x7F | 0x80) = end range at 0x0FFFFFFF */
	__raw_writel(0x8843407F, GDROM_DMA_ACCESS_CTRL_REG);
	__raw_writel(9, GDROM_DMA_WAIT_REG); /* DMA word setting */
	return 0;
}