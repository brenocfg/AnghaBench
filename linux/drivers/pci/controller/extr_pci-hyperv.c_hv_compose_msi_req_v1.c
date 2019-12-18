#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_6__ {int vector_count; int /*<<< orphan*/  cpu_mask; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {int slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct pci_create_interrupt {TYPE_3__ int_desc; TYPE_2__ wslot; TYPE_1__ message_type; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_AFFINITY_ALL ; 
 int /*<<< orphan*/  PCI_CREATE_INTERRUPT_MESSAGE ; 
 int /*<<< orphan*/  dest_Fixed ; 

__attribute__((used)) static u32 hv_compose_msi_req_v1(
	struct pci_create_interrupt *int_pkt, struct cpumask *affinity,
	u32 slot, u8 vector)
{
	int_pkt->message_type.type = PCI_CREATE_INTERRUPT_MESSAGE;
	int_pkt->wslot.slot = slot;
	int_pkt->int_desc.vector = vector;
	int_pkt->int_desc.vector_count = 1;
	int_pkt->int_desc.delivery_mode = dest_Fixed;

	/*
	 * Create MSI w/ dummy vCPU set, overwritten by subsequent retarget in
	 * hv_irq_unmask().
	 */
	int_pkt->int_desc.cpu_mask = CPU_AFFINITY_ALL;

	return sizeof(*int_pkt);
}