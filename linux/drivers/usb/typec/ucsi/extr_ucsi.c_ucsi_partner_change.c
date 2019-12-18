#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int partner_type; } ;
struct ucsi_connector {int /*<<< orphan*/  num; TYPE_1__* ucsi; int /*<<< orphan*/  complete; int /*<<< orphan*/  port; TYPE_2__ status; int /*<<< orphan*/  partner; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_DEVICE ; 
 int /*<<< orphan*/  TYPEC_HOST ; 
#define  UCSI_CONSTAT_PARTNER_TYPE_DFP 129 
#define  UCSI_CONSTAT_PARTNER_TYPE_UFP 128 
 int /*<<< orphan*/  UCSI_RECIPIENT_SOP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_set_data_role (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucsi_altmode_update_active (struct ucsi_connector*) ; 
 int ucsi_register_altmodes (struct ucsi_connector*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ucsi_partner_change(struct ucsi_connector *con)
{
	int ret;

	if (!con->partner)
		return;

	switch (con->status.partner_type) {
	case UCSI_CONSTAT_PARTNER_TYPE_UFP:
		typec_set_data_role(con->port, TYPEC_HOST);
		break;
	case UCSI_CONSTAT_PARTNER_TYPE_DFP:
		typec_set_data_role(con->port, TYPEC_DEVICE);
		break;
	default:
		break;
	}

	/* Complete pending data role swap */
	if (!completion_done(&con->complete))
		complete(&con->complete);

	/* Can't rely on Partner Flags field. Always checking the alt modes. */
	ret = ucsi_register_altmodes(con, UCSI_RECIPIENT_SOP);
	if (ret)
		dev_err(con->ucsi->dev,
			"con%d: failed to register partner alternate modes\n",
			con->num);
	else
		ucsi_altmode_update_active(con);
}