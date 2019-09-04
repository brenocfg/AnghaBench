#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct adf_etr_ring_data {scalar_t__ head; int /*<<< orphan*/  ring_number; TYPE_1__* bank; scalar_t__ base_addr; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  msg_size; int /*<<< orphan*/  inflights; int /*<<< orphan*/  (* callback ) (scalar_t__*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;

/* Variables and functions */
 scalar_t__ ADF_MSG_SIZE_TO_BYTES (int /*<<< orphan*/ ) ; 
 scalar_t__ ADF_RING_EMPTY_SIG ; 
 int /*<<< orphan*/  ADF_RING_SIZE_MODULO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_CSR_RING_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ adf_modulo (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 

__attribute__((used)) static int adf_handle_response(struct adf_etr_ring_data *ring)
{
	uint32_t msg_counter = 0;
	uint32_t *msg = (uint32_t *)((uintptr_t)ring->base_addr + ring->head);

	while (*msg != ADF_RING_EMPTY_SIG) {
		ring->callback((uint32_t *)msg);
		atomic_dec(ring->inflights);
		*msg = ADF_RING_EMPTY_SIG;
		ring->head = adf_modulo(ring->head +
					ADF_MSG_SIZE_TO_BYTES(ring->msg_size),
					ADF_RING_SIZE_MODULO(ring->ring_size));
		msg_counter++;
		msg = (uint32_t *)((uintptr_t)ring->base_addr + ring->head);
	}
	if (msg_counter > 0)
		WRITE_CSR_RING_HEAD(ring->bank->csr_addr,
				    ring->bank->bank_number,
				    ring->ring_number, ring->head);
	return 0;
}