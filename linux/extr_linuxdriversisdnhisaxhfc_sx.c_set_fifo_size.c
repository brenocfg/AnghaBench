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
struct TYPE_4__ {int chip; int cirm; scalar_t__ b_fifo_size; } ;
struct TYPE_3__ {TYPE_2__ hfcsx; } ;
struct IsdnCardState {TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ B_FIFO_SIZE_32K ; 
 scalar_t__ B_FIFO_SIZE_8K ; 

__attribute__((used)) static int set_fifo_size(struct IsdnCardState *cs)
{

	if (cs->hw.hfcsx.b_fifo_size) return (1); /* already determined */

	if ((cs->hw.hfcsx.chip >> 4) == 9) {
		cs->hw.hfcsx.b_fifo_size = B_FIFO_SIZE_32K;
		return (1);
	}

	cs->hw.hfcsx.b_fifo_size = B_FIFO_SIZE_8K;
	cs->hw.hfcsx.cirm |= 0x10; /* only 8K of ram */
	return (0);

}