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
typedef  int /*<<< orphan*/  u16 ;
struct typec_partner_desc {int usb_pd; int /*<<< orphan*/ * identity; int /*<<< orphan*/  accessory; } ;
struct tps6598x {int /*<<< orphan*/  partner; int /*<<< orphan*/  port; int /*<<< orphan*/  partner_identity; } ;
typedef  enum typec_pwr_opmode { ____Placeholder_typec_pwr_opmode } typec_pwr_opmode ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int TPS_POWER_STATUS_PWROPMODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS_REG_POWER_STATUS ; 
 int /*<<< orphan*/  TPS_STATUS_DATAROLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS_STATUS_PORTROLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPS_STATUS_VCONN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEC_ACCESSORY_NONE ; 
 int TYPEC_PWR_MODE_PD ; 
 int tps6598x_read16 (struct tps6598x*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tps6598x_read_partner_identity (struct tps6598x*) ; 
 int /*<<< orphan*/  typec_partner_set_identity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_register_partner (int /*<<< orphan*/ ,struct typec_partner_desc*) ; 
 int /*<<< orphan*/  typec_set_data_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_pwr_opmode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  typec_set_pwr_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_vconn_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps6598x_connect(struct tps6598x *tps, u32 status)
{
	struct typec_partner_desc desc;
	enum typec_pwr_opmode mode;
	u16 pwr_status;
	int ret;

	if (tps->partner)
		return 0;

	ret = tps6598x_read16(tps, TPS_REG_POWER_STATUS, &pwr_status);
	if (ret < 0)
		return ret;

	mode = TPS_POWER_STATUS_PWROPMODE(pwr_status);

	desc.usb_pd = mode == TYPEC_PWR_MODE_PD;
	desc.accessory = TYPEC_ACCESSORY_NONE; /* XXX: handle accessories */
	desc.identity = NULL;

	if (desc.usb_pd) {
		ret = tps6598x_read_partner_identity(tps);
		if (ret)
			return ret;
		desc.identity = &tps->partner_identity;
	}

	typec_set_pwr_opmode(tps->port, mode);
	typec_set_pwr_role(tps->port, TPS_STATUS_PORTROLE(status));
	typec_set_vconn_role(tps->port, TPS_STATUS_VCONN(status));
	typec_set_data_role(tps->port, TPS_STATUS_DATAROLE(status));

	tps->partner = typec_register_partner(tps->port, &desc);
	if (IS_ERR(tps->partner))
		return PTR_ERR(tps->partner);

	if (desc.identity)
		typec_partner_set_identity(tps->partner);

	return 0;
}