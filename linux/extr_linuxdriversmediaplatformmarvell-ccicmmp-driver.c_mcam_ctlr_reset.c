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
struct mmp_camera {scalar_t__ power_regs; } ;
struct mcam_camera {scalar_t__ ccic_id; } ;

/* Variables and functions */
 scalar_t__ REG_CCIC2_CRCR ; 
 scalar_t__ REG_CCIC_CRCR ; 
 unsigned long ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned long,scalar_t__) ; 
 struct mmp_camera* mcam_to_cam (struct mcam_camera*) ; 

__attribute__((used)) static void mcam_ctlr_reset(struct mcam_camera *mcam)
{
	unsigned long val;
	struct mmp_camera *cam = mcam_to_cam(mcam);

	if (mcam->ccic_id) {
		/*
		 * Using CCIC2
		 */
		val = ioread32(cam->power_regs + REG_CCIC2_CRCR);
		iowrite32(val & ~0x2, cam->power_regs + REG_CCIC2_CRCR);
		iowrite32(val | 0x2, cam->power_regs + REG_CCIC2_CRCR);
	} else {
		/*
		 * Using CCIC1
		 */
		val = ioread32(cam->power_regs + REG_CCIC_CRCR);
		iowrite32(val & ~0x2, cam->power_regs + REG_CCIC_CRCR);
		iowrite32(val | 0x2, cam->power_regs + REG_CCIC_CRCR);
	}
}