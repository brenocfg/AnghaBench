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
struct radeonfb_info {scalar_t__ family; int video_ram; int vram_ddr; int vram_width; TYPE_1__* pdev; scalar_t__ is_IGP; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 scalar_t__ CHIP_FAMILY_R300 ; 
 scalar_t__ CHIP_FAMILY_RC410 ; 
 scalar_t__ CHIP_FAMILY_RS100 ; 
 scalar_t__ CHIP_FAMILY_RS200 ; 
 scalar_t__ CHIP_FAMILY_RS300 ; 
 scalar_t__ CHIP_FAMILY_RS400 ; 
 scalar_t__ CHIP_FAMILY_RS480 ; 
 scalar_t__ CHIP_FAMILY_RV100 ; 
 int /*<<< orphan*/  CNFG_MEMSIZE ; 
 int CNFG_MEMSIZE_MASK ; 
 int /*<<< orphan*/  CRTC2_DISPLAY_BASE_ADDR ; 
 int /*<<< orphan*/  CRTC_H_CUTOFF_ACTIVE_EN ; 
 int /*<<< orphan*/  CRTC_MORE_CNTL ; 
 int /*<<< orphan*/  DISPLAY_BASE_ADDR ; 
 int /*<<< orphan*/  GRPH2_BUFFER_CNTL ; 
 int INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_R300_VARIANT (struct radeonfb_info*) ; 
 int /*<<< orphan*/  MC_FB_LOCATION ; 
 int /*<<< orphan*/  MEM_CNTL ; 
 int MEM_NUM_CHANNELS_MASK ; 
 int /*<<< orphan*/  MEM_SDRAM_MODE_REG ; 
 int /*<<< orphan*/  NB_TOM ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTREGP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV0_BASE_ADDR ; 
#define  PCI_CHIP_RADEON_LY 129 
#define  PCI_CHIP_RADEON_LZ 128 
 int R300_MEM_NUM_CHANNELS_MASK ; 
 int RV100_MEM_HALF_MODE ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  radeon_fifo_wait (int) ; 

__attribute__((used)) static void radeon_identify_vram(struct radeonfb_info *rinfo)
{
	u32 tmp;

	/* framebuffer size */
        if ((rinfo->family == CHIP_FAMILY_RS100) ||
            (rinfo->family == CHIP_FAMILY_RS200) ||
            (rinfo->family == CHIP_FAMILY_RS300) ||
            (rinfo->family == CHIP_FAMILY_RC410) ||
            (rinfo->family == CHIP_FAMILY_RS400) ||
	    (rinfo->family == CHIP_FAMILY_RS480) ) {
          u32 tom = INREG(NB_TOM);
          tmp = ((((tom >> 16) - (tom & 0xffff) + 1) << 6) * 1024);

 		radeon_fifo_wait(6);
          OUTREG(MC_FB_LOCATION, tom);
          OUTREG(DISPLAY_BASE_ADDR, (tom & 0xffff) << 16);
          OUTREG(CRTC2_DISPLAY_BASE_ADDR, (tom & 0xffff) << 16);
          OUTREG(OV0_BASE_ADDR, (tom & 0xffff) << 16);

          /* This is supposed to fix the crtc2 noise problem. */
          OUTREG(GRPH2_BUFFER_CNTL, INREG(GRPH2_BUFFER_CNTL) & ~0x7f0000);

          if ((rinfo->family == CHIP_FAMILY_RS100) ||
              (rinfo->family == CHIP_FAMILY_RS200)) {
             /* This is to workaround the asic bug for RMX, some versions
                of BIOS doesn't have this register initialized correctly.
             */
             OUTREGP(CRTC_MORE_CNTL, CRTC_H_CUTOFF_ACTIVE_EN,
                     ~CRTC_H_CUTOFF_ACTIVE_EN);
          }
        } else {
          tmp = INREG(CNFG_MEMSIZE);
        }

	/* mem size is bits [28:0], mask off the rest */
	rinfo->video_ram = tmp & CNFG_MEMSIZE_MASK;

	/*
	 * Hack to get around some busted production M6's
	 * reporting no ram
	 */
	if (rinfo->video_ram == 0) {
		switch (rinfo->pdev->device) {
	       	case PCI_CHIP_RADEON_LY:
		case PCI_CHIP_RADEON_LZ:
	       		rinfo->video_ram = 8192 * 1024;
	       		break;
	       	default:
	       		break;
		}
	}


	/*
	 * Now try to identify VRAM type
	 */
	if (rinfo->is_IGP || (rinfo->family >= CHIP_FAMILY_R300) ||
	    (INREG(MEM_SDRAM_MODE_REG) & (1<<30)))
		rinfo->vram_ddr = 1;
	else
		rinfo->vram_ddr = 0;

	tmp = INREG(MEM_CNTL);
	if (IS_R300_VARIANT(rinfo)) {
		tmp &=  R300_MEM_NUM_CHANNELS_MASK;
		switch (tmp) {
		case 0:  rinfo->vram_width = 64; break;
		case 1:  rinfo->vram_width = 128; break;
		case 2:  rinfo->vram_width = 256; break;
		default: rinfo->vram_width = 128; break;
		}
	} else if ((rinfo->family == CHIP_FAMILY_RV100) ||
		   (rinfo->family == CHIP_FAMILY_RS100) ||
		   (rinfo->family == CHIP_FAMILY_RS200)){
		if (tmp & RV100_MEM_HALF_MODE)
			rinfo->vram_width = 32;
		else
			rinfo->vram_width = 64;
	} else {
		if (tmp & MEM_NUM_CHANNELS_MASK)
			rinfo->vram_width = 128;
		else
			rinfo->vram_width = 64;
	}

	/* This may not be correct, as some cards can have half of channel disabled
	 * ToDo: identify these cases
	 */

	pr_debug("radeonfb (%s): Found %ldk of %s %d bits wide videoram\n",
	       pci_name(rinfo->pdev),
	       rinfo->video_ram / 1024,
	       rinfo->vram_ddr ? "DDR" : "SDRAM",
	       rinfo->vram_width);
}