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

/* Variables and functions */
 int CLC_RMC ; 
 int CLC_SUSPEND ; 
 int /*<<< orphan*/  GPTU_CLC ; 
 int /*<<< orphan*/  GPTU_IRNCR ; 
 int /*<<< orphan*/  GPTU_IRNEN ; 
 int /*<<< orphan*/  gptu_w32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gptu_hwinit(void)
{
	gptu_w32(0x00, GPTU_IRNEN);
	gptu_w32(0xff, GPTU_IRNCR);
	gptu_w32(CLC_RMC | CLC_SUSPEND, GPTU_CLC);
}