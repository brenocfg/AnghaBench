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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int u8 ;
typedef  int u16 ;
struct bfa_fcs_fabric_s {TYPE_1__* lps; } ;
struct TYPE_2__ {int /*<<< orphan*/  pr_nwwn; } ;

/* Variables and functions */

u16
bfa_fcs_fabric_get_switch_oui(struct bfa_fcs_fabric_s *fabric)
{
	wwn_t fab_nwwn;
	u8 *tmp;
	u16 oui;

	fab_nwwn = fabric->lps->pr_nwwn;

	tmp = (u8 *)&fab_nwwn;
	oui = (tmp[3] << 8) | tmp[4];

	return oui;
}