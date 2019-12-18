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
 scalar_t__ CPU_STATE ; 
 int /*<<< orphan*/  tw32 (scalar_t__,int) ; 
 int /*<<< orphan*/  tw32_f (scalar_t__,int) ; 

__attribute__((used)) static void tg3_resume_cpu(struct tg3 *tp, u32 cpu_base)
{
	tw32(cpu_base + CPU_STATE, 0xffffffff);
	tw32_f(cpu_base + CPU_MODE,  0x00000000);
}