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
typedef  int u32 ;
struct mt2063_state {int* CTFiltMax; } ;

/* Variables and functions */

__attribute__((used)) static u32 FindClearTuneFilter(struct mt2063_state *state, u32 f_in)
{
	u32 RFBand;
	u32 idx;		/*  index loop                      */

	/*
	 **  Find RF Band setting
	 */
	RFBand = 31;		/*  def when f_in > all    */
	for (idx = 0; idx < 31; ++idx) {
		if (state->CTFiltMax[idx] >= f_in) {
			RFBand = idx;
			break;
		}
	}
	return RFBand;
}