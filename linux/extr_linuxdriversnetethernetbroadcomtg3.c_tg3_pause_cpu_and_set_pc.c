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
typedef  scalar_t__ u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPU_MODE ; 
 int CPU_MODE_HALT ; 
 scalar_t__ CPU_PC ; 
 scalar_t__ CPU_STATE ; 
 int EBUSY ; 
 scalar_t__ tr32 (scalar_t__) ; 
 int /*<<< orphan*/  tw32 (scalar_t__,int) ; 
 int /*<<< orphan*/  tw32_f (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_pause_cpu_and_set_pc(struct tg3 *tp, u32 cpu_base, u32 pc)
{
	int i;
	const int iters = 5;

	tw32(cpu_base + CPU_STATE, 0xffffffff);
	tw32_f(cpu_base + CPU_PC, pc);

	for (i = 0; i < iters; i++) {
		if (tr32(cpu_base + CPU_PC) == pc)
			break;
		tw32(cpu_base + CPU_STATE, 0xffffffff);
		tw32(cpu_base + CPU_MODE,  CPU_MODE_HALT);
		tw32_f(cpu_base + CPU_PC, pc);
		udelay(1000);
	}

	return (i == iters) ? -EBUSY : 0;
}