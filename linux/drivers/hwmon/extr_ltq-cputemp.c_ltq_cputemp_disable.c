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
 int /*<<< orphan*/  CGU_GPHY1_CR ; 
 int CGU_TEMP_PD ; 
 int ltq_cgu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_cgu_w32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltq_cputemp_disable(void *data)
{
	ltq_cgu_w32(ltq_cgu_r32(CGU_GPHY1_CR) & ~CGU_TEMP_PD, CGU_GPHY1_CR);
}