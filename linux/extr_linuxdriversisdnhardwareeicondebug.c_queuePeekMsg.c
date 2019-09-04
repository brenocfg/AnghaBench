#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_5__ {int Size; } ;
struct TYPE_4__ {int /*<<< orphan*/  Wrap; int /*<<< orphan*/ * Tail; scalar_t__ Head; } ;
typedef  TYPE_1__ MSG_QUEUE ;
typedef  TYPE_2__ MSG_HEAD ;

/* Variables and functions */
 int MSG_INCOMPLETE ; 

__attribute__((used)) static byte *queuePeekMsg(MSG_QUEUE *Q, word *size) {
	/* Show the first valid message in queue BUT DON'T free the message.
	 * After looking on the message contents it can be freed queueFreeMsg()
	 * or simply remain in message queue.  */

	MSG_HEAD *Msg = (MSG_HEAD *)Q->Head;

	if (((byte *)Msg == Q->Tail && !Q->Wrap) ||
	    (Msg->Size & MSG_INCOMPLETE)) {
		return NULL;
	} else {
		*size = Msg->Size;
		return ((byte *)(Msg + 1));
	}
}