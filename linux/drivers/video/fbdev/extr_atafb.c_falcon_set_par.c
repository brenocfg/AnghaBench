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
struct TYPE_4__ {int /*<<< orphan*/  falcon; } ;
struct atafb_par {scalar_t__ screen_base; TYPE_1__ hw; } ;
struct TYPE_6__ {scalar_t__ screen_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_screen_base ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ DontCalcRes ; 
 TYPE_3__ current_par ; 
 int f_change_mode ; 
 int /*<<< orphan*/  f_new_mode ; 
 TYPE_2__* fbhw ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void falcon_set_par(struct atafb_par *par)
{
	f_change_mode = 0;

	/* only set screen_base if really necessary */
	if (current_par.screen_base != par->screen_base)
		fbhw->set_screen_base(par->screen_base);

	/* Don't touch any other registers if we keep the default resolution */
	if (DontCalcRes)
		return;

	/* Tell vbl-handler to change video mode.
	 * We change modes only on next VBL, to avoid desynchronisation
	 * (a shift to the right and wrap around by a random number of pixels
	 * in all monochrome modes).
	 * This seems to work on my Falcon.
	 */
	f_new_mode = par->hw.falcon;
	f_change_mode = 1;
}