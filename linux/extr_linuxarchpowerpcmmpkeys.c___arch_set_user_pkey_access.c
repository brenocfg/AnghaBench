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
typedef  int u64 ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int AMR_RD_BIT ; 
 int AMR_WR_BIT ; 
 int EINVAL ; 
 int IAMR_EX_BIT ; 
 unsigned long PKEY_DISABLE_ACCESS ; 
 unsigned long PKEY_DISABLE_EXECUTE ; 
 unsigned long PKEY_DISABLE_WRITE ; 
 int /*<<< orphan*/  init_amr (int,int) ; 
 int /*<<< orphan*/  init_iamr (int,int) ; 
 int /*<<< orphan*/  is_pkey_enabled (int) ; 
 int /*<<< orphan*/  pkey_execute_disable_supported ; 

int __arch_set_user_pkey_access(struct task_struct *tsk, int pkey,
				unsigned long init_val)
{
	u64 new_amr_bits = 0x0ul;
	u64 new_iamr_bits = 0x0ul;

	if (!is_pkey_enabled(pkey))
		return -EINVAL;

	if (init_val & PKEY_DISABLE_EXECUTE) {
		if (!pkey_execute_disable_supported)
			return -EINVAL;
		new_iamr_bits |= IAMR_EX_BIT;
	}
	init_iamr(pkey, new_iamr_bits);

	/* Set the bits we need in AMR: */
	if (init_val & PKEY_DISABLE_ACCESS)
		new_amr_bits |= AMR_RD_BIT | AMR_WR_BIT;
	else if (init_val & PKEY_DISABLE_WRITE)
		new_amr_bits |= AMR_WR_BIT;

	init_amr(pkey, new_amr_bits);
	return 0;
}