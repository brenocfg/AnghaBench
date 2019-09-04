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
struct vmci_qp_page_store {int len; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
VMCI_QP_PAGESTORE_IS_WELLFORMED(struct vmci_qp_page_store *page_store)
{
	return page_store->len >= 2;
}