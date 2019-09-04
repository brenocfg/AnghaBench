#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {int Size; scalar_t__ Count; int /*<<< orphan*/ * Wrap; int /*<<< orphan*/ * High; int /*<<< orphan*/ * Tail; int /*<<< orphan*/ * Head; int /*<<< orphan*/ * Base; } ;
typedef  TYPE_1__ MSG_QUEUE ;

/* Variables and functions */

__attribute__((used)) static void queueInit(MSG_QUEUE *Q, byte *Buffer, dword sizeBuffer) {
	Q->Size = sizeBuffer;
	Q->Base = Q->Head = Q->Tail = Buffer;
	Q->High = Buffer + sizeBuffer;
	Q->Wrap = NULL;
	Q->Count = 0;
}