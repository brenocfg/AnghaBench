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
struct hfc_pci {struct bchannel* bch; } ;
struct bchannel {int nr; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bchannel *
Sel_BCS(struct hfc_pci *hc, int channel)
{
	if (test_bit(FLG_ACTIVE, &hc->bch[0].Flags) &&
	    (hc->bch[0].nr & channel))
		return &hc->bch[0];
	else if (test_bit(FLG_ACTIVE, &hc->bch[1].Flags) &&
		 (hc->bch[1].nr & channel))
		return &hc->bch[1];
	else
		return NULL;
}