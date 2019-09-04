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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FVTHROT_DTC0 ; 
 int /*<<< orphan*/  FVTHROT_DTC1 ; 
 int /*<<< orphan*/  FVTHROT_DTC2 ; 
 int /*<<< orphan*/  FVTHROT_DTC3 ; 
 int /*<<< orphan*/  FVTHROT_DTC4 ; 
 int /*<<< orphan*/  FVTHROT_UTC0 ; 
 int /*<<< orphan*/  FVTHROT_UTC1 ; 
 int /*<<< orphan*/  FVTHROT_UTC2 ; 
 int /*<<< orphan*/  FVTHROT_UTC3 ; 
 int /*<<< orphan*/  FVTHROT_UTC4 ; 
 int /*<<< orphan*/  RS780_FVTHROTDTC0_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTDTC1_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTDTC2_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTDTC3_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTDTC4_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTUTC0_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTUTC1_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTUTC2_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTUTC3_DFLT ; 
 int /*<<< orphan*/  RS780_FVTHROTUTC4_DFLT ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs780_set_engine_clock_wfc(struct radeon_device *rdev)
{
	WREG32(FVTHROT_UTC0, RS780_FVTHROTUTC0_DFLT);
	WREG32(FVTHROT_UTC1, RS780_FVTHROTUTC1_DFLT);
	WREG32(FVTHROT_UTC2, RS780_FVTHROTUTC2_DFLT);
	WREG32(FVTHROT_UTC3, RS780_FVTHROTUTC3_DFLT);
	WREG32(FVTHROT_UTC4, RS780_FVTHROTUTC4_DFLT);

	WREG32(FVTHROT_DTC0, RS780_FVTHROTDTC0_DFLT);
	WREG32(FVTHROT_DTC1, RS780_FVTHROTDTC1_DFLT);
	WREG32(FVTHROT_DTC2, RS780_FVTHROTDTC2_DFLT);
	WREG32(FVTHROT_DTC3, RS780_FVTHROTDTC3_DFLT);
	WREG32(FVTHROT_DTC4, RS780_FVTHROTDTC4_DFLT);
}