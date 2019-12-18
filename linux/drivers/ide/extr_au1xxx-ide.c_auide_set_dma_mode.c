#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ide_hwif_t ;
struct TYPE_3__ {int dma_mode; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDMA0 ; 
 int /*<<< orphan*/  MDMA1 ; 
 int /*<<< orphan*/  MDMA2 ; 
 int /*<<< orphan*/  MEM_STCFG2 ; 
 int /*<<< orphan*/  MEM_STTIME2 ; 
 int SBC_IDE_MDMA0_TCSOE ; 
 int SBC_IDE_MDMA0_TOECS ; 
 int SBC_IDE_MDMA1_TCSOE ; 
 int SBC_IDE_MDMA1_TOECS ; 
 int SBC_IDE_MDMA2_TCSOE ; 
 int SBC_IDE_MDMA2_TOECS ; 
 int SBC_IDE_TIMING (int /*<<< orphan*/ ) ; 
 int TCSOE_MASK ; 
 int TOECS_MASK ; 
 int TS_MASK ; 
#define  XFER_MW_DMA_0 130 
#define  XFER_MW_DMA_1 129 
#define  XFER_MW_DMA_2 128 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void auide_set_dma_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	int mem_sttime = 0, mem_stcfg = au_readl(MEM_STCFG2);

	switch (drive->dma_mode) {
#ifdef CONFIG_BLK_DEV_IDE_AU1XXX_MDMA2_DBDMA
	case XFER_MW_DMA_2:
		mem_sttime = SBC_IDE_TIMING(MDMA2);

		/* set configuration for RCS2# */
		mem_stcfg &= ~TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_MDMA2_TCSOE | SBC_IDE_MDMA2_TOECS;

		break;
	case XFER_MW_DMA_1:
		mem_sttime = SBC_IDE_TIMING(MDMA1);

		/* set configuration for RCS2# */
		mem_stcfg &= ~TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_MDMA1_TCSOE | SBC_IDE_MDMA1_TOECS;

		break;
	case XFER_MW_DMA_0:
		mem_sttime = SBC_IDE_TIMING(MDMA0);

		/* set configuration for RCS2# */
		mem_stcfg |= TS_MASK;
		mem_stcfg &= ~TCSOE_MASK;
		mem_stcfg &= ~TOECS_MASK;
		mem_stcfg |= SBC_IDE_MDMA0_TCSOE | SBC_IDE_MDMA0_TOECS;

		break;
#endif
	}

	au_writel(mem_sttime,MEM_STTIME2);
	au_writel(mem_stcfg,MEM_STCFG2);
}