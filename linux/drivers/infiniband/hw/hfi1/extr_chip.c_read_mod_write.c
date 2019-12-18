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
typedef  int u16 ;
struct hfi1_devdata {int /*<<< orphan*/  irq_src_lock; } ;

/* Variables and functions */
 int BITS_PER_REGISTER ; 
 scalar_t__ CCE_INT_MASK ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_mod_write(struct hfi1_devdata *dd, u16 src, u64 bits,
			   bool set)
{
	u64 reg;
	u16 idx = src / BITS_PER_REGISTER;

	spin_lock(&dd->irq_src_lock);
	reg = read_csr(dd, CCE_INT_MASK + (8 * idx));
	if (set)
		reg |= bits;
	else
		reg &= ~bits;
	write_csr(dd, CCE_INT_MASK + (8 * idx), reg);
	spin_unlock(&dd->irq_src_lock);
}