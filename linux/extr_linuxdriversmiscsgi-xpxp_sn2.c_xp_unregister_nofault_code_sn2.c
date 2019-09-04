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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  sn_register_nofault_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ xp_error_PIOR ; 
 scalar_t__ xp_nofault_PIOR ; 

__attribute__((used)) static void
xp_unregister_nofault_code_sn2(void)
{
	u64 func_addr = *(u64 *)xp_nofault_PIOR;
	u64 err_func_addr = *(u64 *)xp_error_PIOR;

	/* unregister the PIO read nofault code region */
	(void)sn_register_nofault_code(func_addr, err_func_addr,
				       err_func_addr, 1, 0);
}