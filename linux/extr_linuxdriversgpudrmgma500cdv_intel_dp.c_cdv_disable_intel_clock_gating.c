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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DPCUNIT_CLOCK_GATE_DISABLE ; 
 int DPIOUNIT_CLOCK_GATE_DISABLE ; 
 int DPLSUNIT_CLOCK_GATE_DISABLE ; 
 int DPOUNIT_CLOCK_GATE_DISABLE ; 
 int DPUNIT_PIPEA_GATE_DISABLE ; 
 int DPUNIT_PIPEB_GATE_DISABLE ; 
 int /*<<< orphan*/  DSPCLK_GATE_D ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cdv_disable_intel_clock_gating(struct drm_device *dev)
{
	u32 reg_value;
	reg_value = REG_READ(DSPCLK_GATE_D);

	reg_value |= (DPUNIT_PIPEB_GATE_DISABLE |
			DPUNIT_PIPEA_GATE_DISABLE |
			DPCUNIT_CLOCK_GATE_DISABLE |
			DPLSUNIT_CLOCK_GATE_DISABLE |
			DPOUNIT_CLOCK_GATE_DISABLE |
		 	DPIOUNIT_CLOCK_GATE_DISABLE);	

	REG_WRITE(DSPCLK_GATE_D, reg_value);

	udelay(500);		
}