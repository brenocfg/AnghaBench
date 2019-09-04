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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct SRingBufferDescriptor {int MemSize; int NumBuffers; void* PAHead; struct SBufferHeader* Head; } ;
struct TYPE_2__ {void* Next; } ;
struct SBufferHeader {TYPE_1__ ngeneBuffer; struct SBufferHeader* Next; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SIZEOF_SBufferHeader ; 
 int /*<<< orphan*/  memset (struct SBufferHeader*,int /*<<< orphan*/ ,int) ; 
 struct SBufferHeader* pci_alloc_consistent (struct pci_dev*,int,void**) ; 

__attribute__((used)) static int create_ring_buffer(struct pci_dev *pci_dev,
		       struct SRingBufferDescriptor *descr, u32 NumBuffers)
{
	dma_addr_t tmp;
	struct SBufferHeader *Head;
	u32 i;
	u32 MemSize = SIZEOF_SBufferHeader * NumBuffers;
	u64 PARingBufferHead;
	u64 PARingBufferCur;
	u64 PARingBufferNext;
	struct SBufferHeader *Cur, *Next;

	descr->Head = NULL;
	descr->MemSize = 0;
	descr->PAHead = 0;
	descr->NumBuffers = 0;

	if (MemSize < 4096)
		MemSize = 4096;

	Head = pci_alloc_consistent(pci_dev, MemSize, &tmp);
	PARingBufferHead = tmp;

	if (!Head)
		return -ENOMEM;

	memset(Head, 0, MemSize);

	PARingBufferCur = PARingBufferHead;
	Cur = Head;

	for (i = 0; i < NumBuffers - 1; i++) {
		Next = (struct SBufferHeader *)
			(((u8 *) Cur) + SIZEOF_SBufferHeader);
		PARingBufferNext = PARingBufferCur + SIZEOF_SBufferHeader;
		Cur->Next = Next;
		Cur->ngeneBuffer.Next = PARingBufferNext;
		Cur = Next;
		PARingBufferCur = PARingBufferNext;
	}
	/* Last Buffer points back to first one */
	Cur->Next = Head;
	Cur->ngeneBuffer.Next = PARingBufferHead;

	descr->Head       = Head;
	descr->MemSize    = MemSize;
	descr->PAHead     = PARingBufferHead;
	descr->NumBuffers = NumBuffers;

	return 0;
}