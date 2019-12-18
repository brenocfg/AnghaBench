#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct m_can_classdev {TYPE_1__* mcfg; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int off; int num; } ;

/* Variables and functions */
 size_t MRAM_RXB ; 
 size_t MRAM_RXF0 ; 
 size_t MRAM_RXF1 ; 
 size_t MRAM_SIDF ; 
 size_t MRAM_TXB ; 
 size_t MRAM_TXE ; 
 size_t MRAM_XIDF ; 
 int RXB_ELEMENT_SIZE ; 
 int RXF0_ELEMENT_SIZE ; 
 int RXF1_ELEMENT_SIZE ; 
 int const RXFC_FS_MASK ; 
 int const RXFC_FS_SHIFT ; 
 int SIDF_ELEMENT_SIZE ; 
 int const TXBC_NDTB_MASK ; 
 int const TXBC_NDTB_SHIFT ; 
 int TXE_ELEMENT_SIZE ; 
 int XIDF_ELEMENT_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void m_can_of_parse_mram(struct m_can_classdev *cdev,
				const u32 *mram_config_vals)
{
	cdev->mcfg[MRAM_SIDF].off = mram_config_vals[0];
	cdev->mcfg[MRAM_SIDF].num = mram_config_vals[1];
	cdev->mcfg[MRAM_XIDF].off = cdev->mcfg[MRAM_SIDF].off +
			cdev->mcfg[MRAM_SIDF].num * SIDF_ELEMENT_SIZE;
	cdev->mcfg[MRAM_XIDF].num = mram_config_vals[2];
	cdev->mcfg[MRAM_RXF0].off = cdev->mcfg[MRAM_XIDF].off +
			cdev->mcfg[MRAM_XIDF].num * XIDF_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXF0].num = mram_config_vals[3] &
			(RXFC_FS_MASK >> RXFC_FS_SHIFT);
	cdev->mcfg[MRAM_RXF1].off = cdev->mcfg[MRAM_RXF0].off +
			cdev->mcfg[MRAM_RXF0].num * RXF0_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXF1].num = mram_config_vals[4] &
			(RXFC_FS_MASK >> RXFC_FS_SHIFT);
	cdev->mcfg[MRAM_RXB].off = cdev->mcfg[MRAM_RXF1].off +
			cdev->mcfg[MRAM_RXF1].num * RXF1_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXB].num = mram_config_vals[5];
	cdev->mcfg[MRAM_TXE].off = cdev->mcfg[MRAM_RXB].off +
			cdev->mcfg[MRAM_RXB].num * RXB_ELEMENT_SIZE;
	cdev->mcfg[MRAM_TXE].num = mram_config_vals[6];
	cdev->mcfg[MRAM_TXB].off = cdev->mcfg[MRAM_TXE].off +
			cdev->mcfg[MRAM_TXE].num * TXE_ELEMENT_SIZE;
	cdev->mcfg[MRAM_TXB].num = mram_config_vals[7] &
			(TXBC_NDTB_MASK >> TXBC_NDTB_SHIFT);

	dev_dbg(cdev->dev,
		"sidf 0x%x %d xidf 0x%x %d rxf0 0x%x %d rxf1 0x%x %d rxb 0x%x %d txe 0x%x %d txb 0x%x %d\n",
		cdev->mcfg[MRAM_SIDF].off, cdev->mcfg[MRAM_SIDF].num,
		cdev->mcfg[MRAM_XIDF].off, cdev->mcfg[MRAM_XIDF].num,
		cdev->mcfg[MRAM_RXF0].off, cdev->mcfg[MRAM_RXF0].num,
		cdev->mcfg[MRAM_RXF1].off, cdev->mcfg[MRAM_RXF1].num,
		cdev->mcfg[MRAM_RXB].off, cdev->mcfg[MRAM_RXB].num,
		cdev->mcfg[MRAM_TXE].off, cdev->mcfg[MRAM_TXE].num,
		cdev->mcfg[MRAM_TXB].off, cdev->mcfg[MRAM_TXB].num);
}