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
typedef  int /*<<< orphan*/  u32 ;
struct vmci_qp_page_store {int dummy; } ;
struct vmci_handle {int dummy; } ;
struct vmci_ctx {int dummy; } ;

/* Variables and functions */
 int qp_broker_alloc (struct vmci_handle,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmci_qp_page_store*,struct vmci_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int vmci_qp_broker_alloc(struct vmci_handle handle,
			 u32 peer,
			 u32 flags,
			 u32 priv_flags,
			 u64 produce_size,
			 u64 consume_size,
			 struct vmci_qp_page_store *page_store,
			 struct vmci_ctx *context)
{
	return qp_broker_alloc(handle, peer, flags, priv_flags,
			       produce_size, consume_size,
			       page_store, context, NULL, NULL, NULL, NULL);
}