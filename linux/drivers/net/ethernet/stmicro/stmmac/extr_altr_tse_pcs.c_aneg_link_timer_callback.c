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
struct tse_pcs {scalar_t__ autoneg; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  aneg_link_timer ; 
 int /*<<< orphan*/  auto_nego_timer_callback (struct tse_pcs*) ; 
 struct tse_pcs* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct tse_pcs* pcs ; 
 int /*<<< orphan*/  pcs_link_timer_callback (struct tse_pcs*) ; 

__attribute__((used)) static void aneg_link_timer_callback(struct timer_list *t)
{
	struct tse_pcs *pcs = from_timer(pcs, t, aneg_link_timer);

	if (pcs->autoneg == AUTONEG_ENABLE)
		auto_nego_timer_callback(pcs);
	else if (pcs->autoneg == AUTONEG_DISABLE)
		pcs_link_timer_callback(pcs);
}