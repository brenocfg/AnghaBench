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
 int /*<<< orphan*/  MCI_CTL2_CMCI_EN ; 
 int /*<<< orphan*/  MSR_IA32_MCx_CTL2 (int) ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cmci_disable_bank(int bank)
{
	u64 val;

	if (!test_bit(bank, this_cpu_ptr(mce_banks_owned)))
		return;
	rdmsrl(MSR_IA32_MCx_CTL2(bank), val);
	val &= ~MCI_CTL2_CMCI_EN;
	wrmsrl(MSR_IA32_MCx_CTL2(bank), val);
	__clear_bit(bank, this_cpu_ptr(mce_banks_owned));
}