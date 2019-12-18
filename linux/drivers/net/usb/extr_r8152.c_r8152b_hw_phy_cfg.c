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
struct r8152 {int /*<<< orphan*/  flags; int /*<<< orphan*/  eee_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_RESET ; 
 int /*<<< orphan*/  r8152_aldps_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8152b_enable_fc (struct r8152*) ; 
 int /*<<< orphan*/  rtl_eee_enable (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r8152b_hw_phy_cfg(struct r8152 *tp)
{
	rtl_eee_enable(tp, tp->eee_en);
	r8152_aldps_en(tp, true);
	r8152b_enable_fc(tp);

	set_bit(PHY_RESET, &tp->flags);
}