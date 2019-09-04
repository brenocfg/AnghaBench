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
typedef  int u32 ;
struct SRingBufferDescriptor {int NumBuffers; struct SBufferHeader* Head; } ;
struct TYPE_2__ {int /*<<< orphan*/  Number_of_entries_1; int /*<<< orphan*/  Number_of_entries_2; int /*<<< orphan*/  Address_of_first_entry_1; int /*<<< orphan*/  Address_of_first_entry_2; } ;
struct SBufferHeader {struct SBufferHeader* Next; TYPE_1__ ngeneBuffer; int /*<<< orphan*/  scList1; int /*<<< orphan*/  scList2; int /*<<< orphan*/  Buffer1; int /*<<< orphan*/  Buffer2; } ;

/* Variables and functions */

__attribute__((used)) static int FillTSIdleBuffer(struct SRingBufferDescriptor *pIdleBuffer,
			    struct SRingBufferDescriptor *pRingBuffer)
{
	/* Copy pointer to scatter gather list in TSRingbuffer
	   structure for buffer 2
	   Load number of buffer
	*/
	u32 n = pRingBuffer->NumBuffers;

	/* Point to first buffer entry */
	struct SBufferHeader *Cur = pRingBuffer->Head;
	int i;
	/* Loop thru all buffer and set Buffer 2 pointers to TSIdlebuffer */
	for (i = 0; i < n; i++) {
		Cur->Buffer2 = pIdleBuffer->Head->Buffer1;
		Cur->scList2 = pIdleBuffer->Head->scList1;
		Cur->ngeneBuffer.Address_of_first_entry_2 =
			pIdleBuffer->Head->ngeneBuffer.
			Address_of_first_entry_1;
		Cur->ngeneBuffer.Number_of_entries_2 =
			pIdleBuffer->Head->ngeneBuffer.Number_of_entries_1;
		Cur = Cur->Next;
	}
	return 0;
}