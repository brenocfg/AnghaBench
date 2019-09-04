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

/* Variables and functions */
 int DIVIL_LBAR_PMS ; 
 int DIVIL_LBAR_SMB ; 
 int /*<<< orphan*/  DIVIL_MSR_REG (int) ; 
 int /*<<< orphan*/  _rdmsr (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  _wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void divil_lbar_disable(void)
{
	u32 hi, lo;
	int offset;

	for (offset = DIVIL_LBAR_SMB; offset <= DIVIL_LBAR_PMS; offset++) {
		_rdmsr(DIVIL_MSR_REG(offset), &hi, &lo);
		hi &= ~0x01;
		_wrmsr(DIVIL_MSR_REG(offset), hi, lo);
	}
}