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
struct mcam_camera {int mipi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CSI2_CTRL0 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY3 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY5 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY6 ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcam_disable_mipi(struct mcam_camera *mcam)
{
	/* Using Parallel mode or disable MIPI */
	mcam_reg_write(mcam, REG_CSI2_CTRL0, 0x0);
	mcam_reg_write(mcam, REG_CSI2_DPHY3, 0x0);
	mcam_reg_write(mcam, REG_CSI2_DPHY5, 0x0);
	mcam_reg_write(mcam, REG_CSI2_DPHY6, 0x0);
	mcam->mipi_enabled = false;
}