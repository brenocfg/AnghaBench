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
struct tps6598x {int /*<<< orphan*/  port; int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TPS_STATUS_DATAROLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS_STATUS_PORTROLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS_STATUS_VCONN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEC_PWR_MODE_USB ; 
 int /*<<< orphan*/  typec_set_data_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_pwr_opmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_pwr_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_vconn_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_unregister_partner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tps6598x_disconnect(struct tps6598x *tps, u32 status)
{
	if (!IS_ERR(tps->partner))
		typec_unregister_partner(tps->partner);
	tps->partner = NULL;
	typec_set_pwr_opmode(tps->port, TYPEC_PWR_MODE_USB);
	typec_set_pwr_role(tps->port, TPS_STATUS_PORTROLE(status));
	typec_set_vconn_role(tps->port, TPS_STATUS_VCONN(status));
	typec_set_data_role(tps->port, TPS_STATUS_DATAROLE(status));
}