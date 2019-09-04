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
 int /*<<< orphan*/  CP1_REVISION ; 
 int /*<<< orphan*/  FPU_AS_IS ; 
 int /*<<< orphan*/  __enable_fpu (int /*<<< orphan*/ ) ; 
 unsigned long read_32bit_cp1_register (int /*<<< orphan*/ ) ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static inline unsigned long cpu_get_fpu_id(void)
{
	unsigned long tmp, fpu_id;

	tmp = read_c0_status();
	__enable_fpu(FPU_AS_IS);
	fpu_id = read_32bit_cp1_register(CP1_REVISION);
	write_c0_status(tmp);
	return fpu_id;
}