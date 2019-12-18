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
typedef  int u32 ;
struct vmci_ctx {int /*<<< orphan*/  doorbell_array; } ;
struct dbell_cpt_state {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int VMCI_ERROR_MORE_DATA ; 
 int VMCI_ERROR_NO_MEM ; 
 int VMCI_SUCCESS ; 
 struct dbell_cpt_state* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_handle_arr_get_entry (int /*<<< orphan*/ ,int) ; 
 int vmci_handle_arr_get_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmci_ctx_get_chkpt_doorbells(struct vmci_ctx *context,
					u32 *buf_size, void **pbuf)
{
	struct dbell_cpt_state *dbells;
	u32 i, n_doorbells;

	n_doorbells = vmci_handle_arr_get_size(context->doorbell_array);
	if (n_doorbells > 0) {
		size_t data_size = n_doorbells * sizeof(*dbells);
		if (*buf_size < data_size) {
			*buf_size = data_size;
			return VMCI_ERROR_MORE_DATA;
		}

		dbells = kmalloc(data_size, GFP_ATOMIC);
		if (!dbells)
			return VMCI_ERROR_NO_MEM;

		for (i = 0; i < n_doorbells; i++)
			dbells[i].handle = vmci_handle_arr_get_entry(
						context->doorbell_array, i);

		*buf_size = data_size;
		*pbuf = dbells;
	} else {
		*buf_size = 0;
		*pbuf = NULL;
	}

	return VMCI_SUCCESS;
}