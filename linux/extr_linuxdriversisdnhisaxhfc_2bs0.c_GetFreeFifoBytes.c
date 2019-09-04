#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t f1; size_t f2; int* send; } ;
struct TYPE_7__ {TYPE_1__ hfc; } ;
struct BCState {TYPE_5__* cs; TYPE_2__ hw; } ;
struct TYPE_8__ {int fifosize; } ;
struct TYPE_9__ {TYPE_3__ hfc; } ;
struct TYPE_10__ {TYPE_4__ hw; } ;

/* Variables and functions */

__attribute__((used)) static int
GetFreeFifoBytes(struct BCState *bcs)
{
	int s;

	if (bcs->hw.hfc.f1 == bcs->hw.hfc.f2)
		return (bcs->cs->hw.hfc.fifosize);
	s = bcs->hw.hfc.send[bcs->hw.hfc.f1] - bcs->hw.hfc.send[bcs->hw.hfc.f2];
	if (s <= 0)
		s += bcs->cs->hw.hfc.fifosize;
	s = bcs->cs->hw.hfc.fifosize - s;
	return (s);
}