#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ngene {int /*<<< orphan*/  pci_dev; } ;
struct SRingBufferDescriptor {scalar_t__ NumBuffers; int /*<<< orphan*/  PAHead; struct SBufferHeader* Head; int /*<<< orphan*/  MemSize; int /*<<< orphan*/  PASCListMem; struct SBufferHeader* SCListMem; int /*<<< orphan*/  SCListMemSize; int /*<<< orphan*/  Buffer2Length; int /*<<< orphan*/  Buffer1Length; } ;
struct SBufferHeader {TYPE_2__* scList2; struct SBufferHeader* Buffer2; TYPE_1__* scList1; struct SBufferHeader* Buffer1; struct SBufferHeader* Next; } ;
struct TYPE_4__ {int /*<<< orphan*/  Address; } ;
struct TYPE_3__ {int /*<<< orphan*/  Address; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct SBufferHeader*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ringbuffer(struct ngene *dev, struct SRingBufferDescriptor *rb)
{
	struct SBufferHeader *Cur = rb->Head;
	u32 j;

	if (!Cur)
		return;

	for (j = 0; j < rb->NumBuffers; j++, Cur = Cur->Next) {
		if (Cur->Buffer1)
			pci_free_consistent(dev->pci_dev,
					    rb->Buffer1Length,
					    Cur->Buffer1,
					    Cur->scList1->Address);

		if (Cur->Buffer2)
			pci_free_consistent(dev->pci_dev,
					    rb->Buffer2Length,
					    Cur->Buffer2,
					    Cur->scList2->Address);
	}

	if (rb->SCListMem)
		pci_free_consistent(dev->pci_dev, rb->SCListMemSize,
				    rb->SCListMem, rb->PASCListMem);

	pci_free_consistent(dev->pci_dev, rb->MemSize, rb->Head, rb->PAHead);
}