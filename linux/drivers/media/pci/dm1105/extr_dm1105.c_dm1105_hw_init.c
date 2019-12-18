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
struct dm1105_dev {int dummy; } ;

/* Variables and functions */
 int DM1105_DMA_BYTES ; 
 int /*<<< orphan*/  DM1105_DTALENTH ; 
 int /*<<< orphan*/  DM1105_HOST_CTR ; 
 int /*<<< orphan*/  DM1105_INTCNT ; 
 int /*<<< orphan*/  DM1105_IRCTR ; 
 int /*<<< orphan*/  DM1105_IRMODE ; 
 int DM1105_IR_EN ; 
 int /*<<< orphan*/  DM1105_RLEN ; 
 int /*<<< orphan*/  DM1105_SYSTEMCODE ; 
 int DM1105_SYS_CHK ; 
 int /*<<< orphan*/  DM1105_TSCTR ; 
 int /*<<< orphan*/  dm1105_disable_irqs (struct dm1105_dev*) ; 
 int /*<<< orphan*/  dm1105_dma_map (struct dm1105_dev*) ; 
 int /*<<< orphan*/  dm1105_set_dma_addr (struct dm1105_dev*) ; 
 int /*<<< orphan*/  dm_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_writew (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dm1105_hw_init(struct dm1105_dev *dev)
{
	dm1105_disable_irqs(dev);

	dm_writeb(DM1105_HOST_CTR, 0);

	/*DATALEN 188,*/
	dm_writeb(DM1105_DTALENTH, 188);
	/*TS_STRT TS_VALP MSBFIRST TS_MODE ALPAS TSPES*/
	dm_writew(DM1105_TSCTR, 0xc10a);

	/* map DMA and set address */
	dm1105_dma_map(dev);
	dm1105_set_dma_addr(dev);
	/* big buffer */
	dm_writel(DM1105_RLEN, 5 * DM1105_DMA_BYTES);
	dm_writeb(DM1105_INTCNT, 47);

	/* IR NEC mode enable */
	dm_writeb(DM1105_IRCTR, (DM1105_IR_EN | DM1105_SYS_CHK));
	dm_writeb(DM1105_IRMODE, 0);
	dm_writew(DM1105_SYSTEMCODE, 0);

	return 0;
}