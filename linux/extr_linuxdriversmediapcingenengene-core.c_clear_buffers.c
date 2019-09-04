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
struct TYPE_4__ {struct SBufferHeader* Head; } ;
struct ngene_channel {int mode; int /*<<< orphan*/  DataFormatFlags; int /*<<< orphan*/  Capture1Length; TYPE_1__ TSIdleBuffer; scalar_t__ AudioDTOUpdated; int /*<<< orphan*/  AudioDTOValue; struct SBufferHeader* nextBuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  DTOUpdate; } ;
struct TYPE_5__ {TYPE_3__ SR; } ;
struct SBufferHeader {struct SBufferHeader* Next; int /*<<< orphan*/  Buffer1; TYPE_2__ ngeneBuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FillTSBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NGENE_IO_TSOUT ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_buffers(struct ngene_channel *chan)
{
	struct SBufferHeader *Cur = chan->nextBuffer;

	do {
		memset(&Cur->ngeneBuffer.SR, 0, sizeof(Cur->ngeneBuffer.SR));
		if (chan->mode & NGENE_IO_TSOUT)
			FillTSBuffer(Cur->Buffer1,
				     chan->Capture1Length,
				     chan->DataFormatFlags);
		Cur = Cur->Next;
	} while (Cur != chan->nextBuffer);

	if (chan->mode & NGENE_IO_TSOUT) {
		chan->nextBuffer->ngeneBuffer.SR.DTOUpdate =
			chan->AudioDTOValue;
		chan->AudioDTOUpdated = 0;

		Cur = chan->TSIdleBuffer.Head;

		do {
			memset(&Cur->ngeneBuffer.SR, 0,
			       sizeof(Cur->ngeneBuffer.SR));
			FillTSBuffer(Cur->Buffer1,
				     chan->Capture1Length,
				     chan->DataFormatFlags);
			Cur = Cur->Next;
		} while (Cur != chan->TSIdleBuffer.Head);
	}
}