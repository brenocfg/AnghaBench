#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int u32 ;
struct brcms_c_rateset {size_t count; scalar_t__* rates; int /*<<< orphan*/  mcs; } ;
struct brcms_c_info {TYPE_4__* pub; TYPE_3__* hw; TYPE_2__** bandstate; TYPE_1__* band; } ;
struct TYPE_8__ {int _nbands; int /*<<< orphan*/  unit; } ;
struct TYPE_7__ {int /*<<< orphan*/  d11core; } ;
struct TYPE_6__ {struct brcms_c_rateset hw_rateset; } ;
struct TYPE_5__ {int bandtype; struct brcms_c_rateset hw_rateset; } ;

/* Variables and functions */
 int BRCM_BAND_AUTO ; 
 int MCS_TABLE_SIZE ; 
 size_t OTHERBANDUNIT (struct brcms_c_info*) ; 
 int RSPEC_RATE_MASK ; 
 int /*<<< orphan*/  brcms_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_mcs_rate (int) ; 
 int isset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ rspec2rate (int) ; 

__attribute__((used)) static bool brcms_c_valid_rate(struct brcms_c_info *wlc, u32 rspec, int band,
		    bool verbose)
{
	struct brcms_c_rateset *hw_rateset;
	uint i;

	if ((band == BRCM_BAND_AUTO) || (band == wlc->band->bandtype))
		hw_rateset = &wlc->band->hw_rateset;
	else if (wlc->pub->_nbands > 1)
		hw_rateset = &wlc->bandstate[OTHERBANDUNIT(wlc)]->hw_rateset;
	else
		/* other band specified and we are a single band device */
		return false;

	/* check if this is a mimo rate */
	if (is_mcs_rate(rspec)) {
		if ((rspec & RSPEC_RATE_MASK) >= MCS_TABLE_SIZE)
			goto error;

		return isset(hw_rateset->mcs, (rspec & RSPEC_RATE_MASK));
	}

	for (i = 0; i < hw_rateset->count; i++)
		if (hw_rateset->rates[i] == rspec2rate(rspec))
			return true;
 error:
	if (verbose)
		brcms_err(wlc->hw->d11core, "wl%d: valid_rate: rate spec 0x%x "
			  "not in hw_rateset\n", wlc->pub->unit, rspec);

	return false;
}