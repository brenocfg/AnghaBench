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
 int MESSAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_EXIT_RLC_SAFE_MODE ; 
 int REQ ; 
 int /*<<< orphan*/  RLC_GPR_REG2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 

void cik_exit_rlc_safe_mode(struct radeon_device *rdev)
{
	u32 tmp;

	tmp = REQ | MESSAGE(MSG_EXIT_RLC_SAFE_MODE);
	WREG32(RLC_GPR_REG2, tmp);
}