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
typedef  int uint32_t ;
struct adf_etr_bank_data {int irq_mask; int /*<<< orphan*/ * rings; int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;

/* Variables and functions */
 int ADF_ETR_MAX_RINGS_PER_BANK ; 
 int READ_CSR_E_STAT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adf_handle_response (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adf_ring_response_handler(struct adf_etr_bank_data *bank)
{
	uint32_t empty_rings, i;

	empty_rings = READ_CSR_E_STAT(bank->csr_addr, bank->bank_number);
	empty_rings = ~empty_rings & bank->irq_mask;

	for (i = 0; i < ADF_ETR_MAX_RINGS_PER_BANK; ++i) {
		if (empty_rings & (1 << i))
			adf_handle_response(&bank->rings[i]);
	}
}