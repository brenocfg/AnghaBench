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

/* Variables and functions */
 scalar_t__ REG_CCIC_CRCR ; 
 scalar_t__ REG_CCIC_DCGCR ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void mmpcam_power_up_ctlr(struct mmp_camera *cam)
{
	iowrite32(0x3f, cam->power_regs + REG_CCIC_DCGCR);
	iowrite32(0x3805b, cam->power_regs + REG_CCIC_CRCR);
	mdelay(1);
}