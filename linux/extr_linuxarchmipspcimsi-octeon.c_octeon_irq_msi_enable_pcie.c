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
typedef  unsigned long long u64 ;
struct irq_data {int irq; } ;

/* Variables and functions */
 int OCTEON_IRQ_MSI_BIT0 ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/ * mis_ena_reg ; 
 int /*<<< orphan*/  octeon_irq_msi_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void octeon_irq_msi_enable_pcie(struct irq_data *data)
{
	u64 en;
	unsigned long flags;
	int msi_number = data->irq - OCTEON_IRQ_MSI_BIT0;
	int irq_index = msi_number >> 6;
	int irq_bit = msi_number & 0x3f;

	raw_spin_lock_irqsave(&octeon_irq_msi_lock, flags);
	en = cvmx_read_csr(mis_ena_reg[irq_index]);
	en |= 1ull << irq_bit;
	cvmx_write_csr(mis_ena_reg[irq_index], en);
	cvmx_read_csr(mis_ena_reg[irq_index]);
	raw_spin_unlock_irqrestore(&octeon_irq_msi_lock, flags);
}