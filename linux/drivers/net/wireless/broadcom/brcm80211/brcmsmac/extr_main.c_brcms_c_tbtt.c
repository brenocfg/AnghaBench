#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {int /*<<< orphan*/  qvalid; TYPE_1__* bsscfg; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BRCMS_TYPE_ADHOC ; 
 int /*<<< orphan*/  MCMD_DIRFRMQVAL ; 

__attribute__((used)) static void brcms_c_tbtt(struct brcms_c_info *wlc)
{
	if (wlc->bsscfg->type == BRCMS_TYPE_ADHOC)
		/*
		 * DirFrmQ is now valid...defer setting until end
		 * of ATIM window
		 */
		wlc->qvalid |= MCMD_DIRFRMQVAL;
}