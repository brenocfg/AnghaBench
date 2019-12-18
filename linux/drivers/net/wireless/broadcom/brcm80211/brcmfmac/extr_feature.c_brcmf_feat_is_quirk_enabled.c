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
struct brcmf_if {TYPE_1__* drvr; } ;
typedef  enum brcmf_feat_quirk { ____Placeholder_brcmf_feat_quirk } brcmf_feat_quirk ;
struct TYPE_2__ {int chip_quirks; } ;

/* Variables and functions */
 int BIT (int) ; 

bool brcmf_feat_is_quirk_enabled(struct brcmf_if *ifp,
				 enum brcmf_feat_quirk quirk)
{
	return (ifp->drvr->chip_quirks & BIT(quirk));
}