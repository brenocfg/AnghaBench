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
struct srpt_port {int dummy; } ;
struct se_portal_group {TYPE_1__* se_tpg_wwn; } ;
struct TYPE_2__ {struct srpt_port* priv; } ;

/* Variables and functions */

__attribute__((used)) static struct srpt_port *srpt_tpg_to_sport(struct se_portal_group *tpg)
{
	return tpg->se_tpg_wwn->priv;
}