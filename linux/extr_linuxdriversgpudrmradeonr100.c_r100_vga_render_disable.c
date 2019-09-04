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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int C_0003C2_VGA_RAM_EN ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_0003C2_GENMO_WT ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 

void r100_vga_render_disable(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = RREG8(R_0003C2_GENMO_WT);
	WREG8(R_0003C2_GENMO_WT, C_0003C2_VGA_RAM_EN & tmp);
}