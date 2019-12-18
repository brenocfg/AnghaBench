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
typedef  int /*<<< orphan*/  u32 ;
struct brcms_hardware {scalar_t__ sbclk; int /*<<< orphan*/  pllreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_PLLREQ_FLIP ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int /*<<< orphan*/  brcms_b_xtal (struct brcms_hardware*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolclr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mboolisset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_b_pllreq(struct brcms_hardware *wlc_hw, bool set, u32 req_bit)
{
	if (set) {
		if (mboolisset(wlc_hw->pllreq, req_bit))
			return;

		mboolset(wlc_hw->pllreq, req_bit);

		if (mboolisset(wlc_hw->pllreq, BRCMS_PLLREQ_FLIP)) {
			if (!wlc_hw->sbclk)
				brcms_b_xtal(wlc_hw, ON);
		}
	} else {
		if (!mboolisset(wlc_hw->pllreq, req_bit))
			return;

		mboolclr(wlc_hw->pllreq, req_bit);

		if (mboolisset(wlc_hw->pllreq, BRCMS_PLLREQ_FLIP)) {
			if (wlc_hw->sbclk)
				brcms_b_xtal(wlc_hw, OFF);
		}
	}
}