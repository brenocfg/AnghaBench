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
struct ef4_nic {int dummy; } ;
typedef  int /*<<< orphan*/  ef4_dword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_POPULATE_DWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AA_INT_ACK_KER_FIELD ; 
 int /*<<< orphan*/  FR_AA_INT_ACK_KER ; 
 int /*<<< orphan*/  FR_AA_WORK_AROUND_BROKEN_PCI_READS ; 
 int /*<<< orphan*/  ef4_readd (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writed (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void falcon_irq_ack_a1(struct ef4_nic *efx)
{
	ef4_dword_t reg;

	EF4_POPULATE_DWORD_1(reg, FRF_AA_INT_ACK_KER_FIELD, 0xb7eb7e);
	ef4_writed(efx, &reg, FR_AA_INT_ACK_KER);
	ef4_readd(efx, &reg, FR_AA_WORK_AROUND_BROKEN_PCI_READS);
}