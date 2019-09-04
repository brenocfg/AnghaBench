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
typedef  long long u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCE_INT_CLEAR ; 
 int /*<<< orphan*/  CCE_INT_FORCE ; 
 int /*<<< orphan*/  CCE_INT_MASK ; 
 int /*<<< orphan*/  CCE_INT_STATUS ; 
 int EINVAL ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 long long read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,long long) ; 

__attribute__((used)) static int check_int_registers(struct hfi1_devdata *dd)
{
	u64 reg;
	u64 all_bits = ~(u64)0;
	u64 mask;

	/* Clear CceIntMask[0] to avoid raising any interrupts */
	mask = read_csr(dd, CCE_INT_MASK);
	write_csr(dd, CCE_INT_MASK, 0ull);
	reg = read_csr(dd, CCE_INT_MASK);
	if (reg)
		goto err_exit;

	/* Clear all interrupt status bits */
	write_csr(dd, CCE_INT_CLEAR, all_bits);
	reg = read_csr(dd, CCE_INT_STATUS);
	if (reg)
		goto err_exit;

	/* Set all interrupt status bits */
	write_csr(dd, CCE_INT_FORCE, all_bits);
	reg = read_csr(dd, CCE_INT_STATUS);
	if (reg != all_bits)
		goto err_exit;

	/* Restore the interrupt mask */
	write_csr(dd, CCE_INT_CLEAR, all_bits);
	write_csr(dd, CCE_INT_MASK, mask);

	return 0;
err_exit:
	write_csr(dd, CCE_INT_MASK, mask);
	dd_dev_err(dd, "Interrupt registers not properly mapped by VMM\n");
	return -EINVAL;
}