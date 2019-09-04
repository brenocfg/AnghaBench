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
struct ngene {int dummy; } ;
struct SRingBufferDescriptor {int NumBuffers; struct SBufferHeader* Head; } ;
struct TYPE_2__ {scalar_t__ Number_of_entries_2; scalar_t__ Address_of_first_entry_2; } ;
struct SBufferHeader {TYPE_1__ ngeneBuffer; int /*<<< orphan*/ * scList2; int /*<<< orphan*/ * Buffer2; struct SBufferHeader* Next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ringbuffer (struct ngene*,struct SRingBufferDescriptor*) ; 

__attribute__((used)) static void free_idlebuffer(struct ngene *dev,
		     struct SRingBufferDescriptor *rb,
		     struct SRingBufferDescriptor *tb)
{
	int j;
	struct SBufferHeader *Cur = tb->Head;

	if (!rb->Head)
		return;
	free_ringbuffer(dev, rb);
	for (j = 0; j < tb->NumBuffers; j++, Cur = Cur->Next) {
		Cur->Buffer2 = NULL;
		Cur->scList2 = NULL;
		Cur->ngeneBuffer.Address_of_first_entry_2 = 0;
		Cur->ngeneBuffer.Number_of_entries_2 = 0;
	}
}