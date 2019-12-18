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
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct SRingBufferDescriptor {int NumBuffers; int PASCListMem; int SCListMemSize; int Buffer1Length; int Buffer2Length; struct SBufferHeader* Head; void* SCListMem; } ;
struct TYPE_2__ {int Address_of_first_entry_1; int Number_of_entries_1; int Address_of_first_entry_2; int Number_of_entries_2; } ;
struct SBufferHeader {TYPE_1__ ngeneBuffer; struct HW_SCATTER_GATHER_ELEMENT* scList2; void* Buffer2; struct HW_SCATTER_GATHER_ELEMENT* scList1; void* Buffer1; struct SBufferHeader* Next; } ;
struct HW_SCATTER_GATHER_ELEMENT {int Address; int Length; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int NUM_SCATTER_GATHER_ENTRIES ; 
 void* OVERFLOW_BUFFER_SIZE ; 
 void* pci_alloc_consistent (struct pci_dev*,int,void**) ; 

__attribute__((used)) static int AllocateRingBuffers(struct pci_dev *pci_dev,
			       dma_addr_t of,
			       struct SRingBufferDescriptor *pRingBuffer,
			       u32 Buffer1Length, u32 Buffer2Length)
{
	dma_addr_t tmp;
	u32 i, j;
	u32 SCListMemSize = pRingBuffer->NumBuffers
		* ((Buffer2Length != 0) ? (NUM_SCATTER_GATHER_ENTRIES * 2) :
		    NUM_SCATTER_GATHER_ENTRIES)
		* sizeof(struct HW_SCATTER_GATHER_ELEMENT);

	u64 PASCListMem;
	struct HW_SCATTER_GATHER_ELEMENT *SCListEntry;
	u64 PASCListEntry;
	struct SBufferHeader *Cur;
	void *SCListMem;

	if (SCListMemSize < 4096)
		SCListMemSize = 4096;

	SCListMem = pci_alloc_consistent(pci_dev, SCListMemSize, &tmp);

	PASCListMem = tmp;
	if (SCListMem == NULL)
		return -ENOMEM;

	pRingBuffer->SCListMem = SCListMem;
	pRingBuffer->PASCListMem = PASCListMem;
	pRingBuffer->SCListMemSize = SCListMemSize;
	pRingBuffer->Buffer1Length = Buffer1Length;
	pRingBuffer->Buffer2Length = Buffer2Length;

	SCListEntry = SCListMem;
	PASCListEntry = PASCListMem;
	Cur = pRingBuffer->Head;

	for (i = 0; i < pRingBuffer->NumBuffers; i += 1, Cur = Cur->Next) {
		u64 PABuffer;

		void *Buffer = pci_alloc_consistent(pci_dev, Buffer1Length,
						    &tmp);
		PABuffer = tmp;

		if (Buffer == NULL)
			return -ENOMEM;

		Cur->Buffer1 = Buffer;

		SCListEntry->Address = PABuffer;
		SCListEntry->Length  = Buffer1Length;

		Cur->scList1 = SCListEntry;
		Cur->ngeneBuffer.Address_of_first_entry_1 = PASCListEntry;
		Cur->ngeneBuffer.Number_of_entries_1 =
			NUM_SCATTER_GATHER_ENTRIES;

		SCListEntry += 1;
		PASCListEntry += sizeof(struct HW_SCATTER_GATHER_ELEMENT);

#if NUM_SCATTER_GATHER_ENTRIES > 1
		for (j = 0; j < NUM_SCATTER_GATHER_ENTRIES - 1; j += 1) {
			SCListEntry->Address = of;
			SCListEntry->Length = OVERFLOW_BUFFER_SIZE;
			SCListEntry += 1;
			PASCListEntry +=
				sizeof(struct HW_SCATTER_GATHER_ELEMENT);
		}
#endif

		if (!Buffer2Length)
			continue;

		Buffer = pci_alloc_consistent(pci_dev, Buffer2Length, &tmp);
		PABuffer = tmp;

		if (Buffer == NULL)
			return -ENOMEM;

		Cur->Buffer2 = Buffer;

		SCListEntry->Address = PABuffer;
		SCListEntry->Length  = Buffer2Length;

		Cur->scList2 = SCListEntry;
		Cur->ngeneBuffer.Address_of_first_entry_2 = PASCListEntry;
		Cur->ngeneBuffer.Number_of_entries_2 =
			NUM_SCATTER_GATHER_ENTRIES;

		SCListEntry   += 1;
		PASCListEntry += sizeof(struct HW_SCATTER_GATHER_ELEMENT);

#if NUM_SCATTER_GATHER_ENTRIES > 1
		for (j = 0; j < NUM_SCATTER_GATHER_ENTRIES - 1; j++) {
			SCListEntry->Address = of;
			SCListEntry->Length = OVERFLOW_BUFFER_SIZE;
			SCListEntry += 1;
			PASCListEntry +=
				sizeof(struct HW_SCATTER_GATHER_ELEMENT);
		}
#endif

	}

	return 0;
}