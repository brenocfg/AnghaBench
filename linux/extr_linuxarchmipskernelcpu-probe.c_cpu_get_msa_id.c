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
 int /*<<< orphan*/  FPU_64BIT ; 
 int /*<<< orphan*/  __enable_fpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_msa () ; 
 int /*<<< orphan*/  enable_msa () ; 
 unsigned long read_c0_status () ; 
 unsigned long read_msa_ir () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static inline unsigned long cpu_get_msa_id(void)
{
	unsigned long status, msa_id;

	status = read_c0_status();
	__enable_fpu(FPU_64BIT);
	enable_msa();
	msa_id = read_msa_ir();
	disable_msa();
	write_c0_status(status);
	return msa_id;
}