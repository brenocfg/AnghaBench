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
struct qdio_q {int /*<<< orphan*/  irq_ptr; } ;

/* Variables and functions */
 scalar_t__ pci_out_supported (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_siga_sync_all (struct qdio_q*) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 

__attribute__((used)) static inline void qdio_sync_queues(struct qdio_q *q)
{
	/* PCI capable outbound queues will also be scanned so sync them too */
	if (pci_out_supported(q->irq_ptr))
		qdio_siga_sync_all(q);
	else
		qdio_siga_sync_q(q);
}