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
struct ngene {size_t EventQueueReadIndex; size_t EventQueueWriteIndex; int /*<<< orphan*/  (* RxEventNotify ) (struct ngene*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* TxEventNotify ) (struct ngene*,int /*<<< orphan*/ ) ;struct EVENT_BUFFER* EventQueue; } ;
struct EVENT_BUFFER {int UARTStatus; int /*<<< orphan*/  RXCharacter; int /*<<< orphan*/  TimeStamp; } ;

/* Variables and functions */
 int EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  stub1 (struct ngene*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ngene*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_tasklet(unsigned long data)
{
	struct ngene *dev = (struct ngene *)data;

	while (dev->EventQueueReadIndex != dev->EventQueueWriteIndex) {
		struct EVENT_BUFFER Event =
			dev->EventQueue[dev->EventQueueReadIndex];
		dev->EventQueueReadIndex =
			(dev->EventQueueReadIndex + 1) & (EVENT_QUEUE_SIZE - 1);

		if ((Event.UARTStatus & 0x01) && (dev->TxEventNotify))
			dev->TxEventNotify(dev, Event.TimeStamp);
		if ((Event.UARTStatus & 0x02) && (dev->RxEventNotify))
			dev->RxEventNotify(dev, Event.TimeStamp,
					   Event.RXCharacter);
	}
}