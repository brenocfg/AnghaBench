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
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmci_disable_bank (int) ; 
 int /*<<< orphan*/  mce_poll_banks ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __mce_disable_bank(void *arg)
{
	int bank = *((int *)arg);
	__clear_bit(bank, this_cpu_ptr(mce_poll_banks));
	cmci_disable_bank(bank);
}