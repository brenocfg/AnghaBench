#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {TYPE_1__ tt; } ;
struct atafb_par {scalar_t__ screen_base; TYPE_2__ hw; } ;
struct TYPE_12__ {scalar_t__ screen_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* set_screen_base ) (scalar_t__) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  syncmode; } ;
struct TYPE_9__ {int /*<<< orphan*/  tt_shiftmode; } ;

/* Variables and functions */
 TYPE_6__ current_par ; 
 TYPE_5__* fbhw ; 
 TYPE_4__ shifter_st ; 
 TYPE_3__ shifter_tt ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void tt_set_par(struct atafb_par *par)
{
	shifter_tt.tt_shiftmode = par->hw.tt.mode;
	shifter_st.syncmode = par->hw.tt.sync;
	/* only set screen_base if really necessary */
	if (current_par.screen_base != par->screen_base)
		fbhw->set_screen_base(par->screen_base);
}