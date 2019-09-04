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
typedef  int u8 ;

/* Variables and functions */
#define  OMAP_L3_IA_CAM_1 156 
#define  OMAP_L3_IA_CAM_2 155 
#define  OMAP_L3_IA_CAM_3 154 
#define  OMAP_L3_IA_DAP 153 
#define  OMAP_L3_IA_IVA_SS_1 152 
#define  OMAP_L3_IA_IVA_SS_2 151 
#define  OMAP_L3_IA_IVA_SS_3 150 
#define  OMAP_L3_IA_IVA_SS_DMA_1 149 
#define  OMAP_L3_IA_IVA_SS_DMA_2 148 
#define  OMAP_L3_IA_IVA_SS_DMA_3 147 
#define  OMAP_L3_IA_IVA_SS_DMA_4 146 
#define  OMAP_L3_IA_IVA_SS_DMA_5 145 
#define  OMAP_L3_IA_IVA_SS_DMA_6 144 
#define  OMAP_L3_IA_MPU_SS_1 143 
#define  OMAP_L3_IA_MPU_SS_2 142 
#define  OMAP_L3_IA_MPU_SS_3 141 
#define  OMAP_L3_IA_MPU_SS_4 140 
#define  OMAP_L3_IA_MPU_SS_5 139 
#define  OMAP_L3_IA_SGX 138 
#define  OMAP_L3_LCD 137 
#define  OMAP_L3_SAD2D 136 
#define  OMAP_L3_SDMA_RD_1 135 
#define  OMAP_L3_SDMA_RD_2 134 
#define  OMAP_L3_SDMA_RD_3 133 
#define  OMAP_L3_SDMA_RD_4 132 
#define  OMAP_L3_SDMA_WR_1 131 
#define  OMAP_L3_SDMA_WR_2 130 
#define  OMAP_L3_USBHOST 129 
#define  OMAP_L3_USBOTG 128 

__attribute__((used)) static char *omap3_l3_initiator_string(u8 initid)
{
	switch (initid) {
	case OMAP_L3_LCD:
		return "LCD";
	case OMAP_L3_SAD2D:
		return "SAD2D";
	case OMAP_L3_IA_MPU_SS_1:
	case OMAP_L3_IA_MPU_SS_2:
	case OMAP_L3_IA_MPU_SS_3:
	case OMAP_L3_IA_MPU_SS_4:
	case OMAP_L3_IA_MPU_SS_5:
		return "MPU";
	case OMAP_L3_IA_IVA_SS_1:
	case OMAP_L3_IA_IVA_SS_2:
	case OMAP_L3_IA_IVA_SS_3:
		return "IVA_SS";
	case OMAP_L3_IA_IVA_SS_DMA_1:
	case OMAP_L3_IA_IVA_SS_DMA_2:
	case OMAP_L3_IA_IVA_SS_DMA_3:
	case OMAP_L3_IA_IVA_SS_DMA_4:
	case OMAP_L3_IA_IVA_SS_DMA_5:
	case OMAP_L3_IA_IVA_SS_DMA_6:
		return "IVA_SS_DMA";
	case OMAP_L3_IA_SGX:
		return "SGX";
	case OMAP_L3_IA_CAM_1:
	case OMAP_L3_IA_CAM_2:
	case OMAP_L3_IA_CAM_3:
		return "CAM";
	case OMAP_L3_IA_DAP:
		return "DAP";
	case OMAP_L3_SDMA_WR_1:
	case OMAP_L3_SDMA_WR_2:
		return "SDMA_WR";
	case OMAP_L3_SDMA_RD_1:
	case OMAP_L3_SDMA_RD_2:
	case OMAP_L3_SDMA_RD_3:
	case OMAP_L3_SDMA_RD_4:
		return "SDMA_RD";
	case OMAP_L3_USBOTG:
		return "USB_OTG";
	case OMAP_L3_USBHOST:
		return "USB_HOST";
	default:
		return "UNKNOWN Initiator";
	}
}