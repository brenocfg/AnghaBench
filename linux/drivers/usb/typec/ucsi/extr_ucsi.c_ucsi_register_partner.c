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
struct TYPE_4__ {int partner_type; scalar_t__ pwr_op_mode; } ;
struct ucsi_connector {struct typec_partner* partner; int /*<<< orphan*/  num; TYPE_1__* ucsi; int /*<<< orphan*/  port; TYPE_2__ status; } ;
struct typec_partner_desc {int usb_pd; int /*<<< orphan*/  accessory; } ;
struct typec_partner {int dummy; } ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct typec_partner*) ; 
 int PTR_ERR (struct typec_partner*) ; 
 int /*<<< orphan*/  TYPEC_ACCESSORY_AUDIO ; 
 int /*<<< orphan*/  TYPEC_ACCESSORY_DEBUG ; 
#define  UCSI_CONSTAT_PARTNER_TYPE_AUDIO 129 
#define  UCSI_CONSTAT_PARTNER_TYPE_DEBUG 128 
 scalar_t__ UCSI_CONSTAT_PWR_OPMODE_PD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct typec_partner_desc*,int /*<<< orphan*/ ,int) ; 
 struct typec_partner* typec_register_partner (int /*<<< orphan*/ ,struct typec_partner_desc*) ; 

__attribute__((used)) static int ucsi_register_partner(struct ucsi_connector *con)
{
	struct typec_partner_desc desc;
	struct typec_partner *partner;

	if (con->partner)
		return 0;

	memset(&desc, 0, sizeof(desc));

	switch (con->status.partner_type) {
	case UCSI_CONSTAT_PARTNER_TYPE_DEBUG:
		desc.accessory = TYPEC_ACCESSORY_DEBUG;
		break;
	case UCSI_CONSTAT_PARTNER_TYPE_AUDIO:
		desc.accessory = TYPEC_ACCESSORY_AUDIO;
		break;
	default:
		break;
	}

	desc.usb_pd = con->status.pwr_op_mode == UCSI_CONSTAT_PWR_OPMODE_PD;

	partner = typec_register_partner(con->port, &desc);
	if (IS_ERR(partner)) {
		dev_err(con->ucsi->dev,
			"con%d: failed to register partner (%ld)\n", con->num,
			PTR_ERR(partner));
		return PTR_ERR(partner);
	}

	con->partner = partner;

	return 0;
}