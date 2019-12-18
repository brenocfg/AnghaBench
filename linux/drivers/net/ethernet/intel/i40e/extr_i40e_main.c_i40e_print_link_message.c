#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {int current_isup; int current_speed; int /*<<< orphan*/  netdev; struct i40e_pf* back; } ;
struct TYPE_8__ {int link_speed; int an_info; int fec_info; int req_fec_info; } ;
struct TYPE_9__ {TYPE_3__ link_info; } ;
struct TYPE_7__ {int current_mode; } ;
struct TYPE_6__ {scalar_t__ npar_enable; } ;
struct TYPE_10__ {TYPE_4__ phy; TYPE_2__ fc; TYPE_1__ func_caps; } ;
struct i40e_pf {TYPE_5__ hw; } ;
typedef  enum i40e_aq_link_speed { ____Placeholder_i40e_aq_link_speed } i40e_aq_link_speed ;

/* Variables and functions */
 int I40E_AQ_AN_COMPLETED ; 
 int I40E_AQ_CONFIG_FEC_KR_ENA ; 
 int I40E_AQ_CONFIG_FEC_RS_ENA ; 
 int I40E_AQ_REQUEST_FEC_KR ; 
 int I40E_AQ_REQUEST_FEC_RS ; 
#define  I40E_FC_FULL 138 
#define  I40E_FC_RX_PAUSE 137 
#define  I40E_FC_TX_PAUSE 136 
#define  I40E_LINK_SPEED_100MB 135 
#define  I40E_LINK_SPEED_10GB 134 
#define  I40E_LINK_SPEED_1GB 133 
#define  I40E_LINK_SPEED_20GB 132 
#define  I40E_LINK_SPEED_25GB 131 
#define  I40E_LINK_SPEED_2_5GB 130 
#define  I40E_LINK_SPEED_40GB 129 
#define  I40E_LINK_SPEED_5GB 128 
 int I40E_LINK_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

void i40e_print_link_message(struct i40e_vsi *vsi, bool isup)
{
	enum i40e_aq_link_speed new_speed;
	struct i40e_pf *pf = vsi->back;
	char *speed = "Unknown";
	char *fc = "Unknown";
	char *fec = "";
	char *req_fec = "";
	char *an = "";

	if (isup)
		new_speed = pf->hw.phy.link_info.link_speed;
	else
		new_speed = I40E_LINK_SPEED_UNKNOWN;

	if ((vsi->current_isup == isup) && (vsi->current_speed == new_speed))
		return;
	vsi->current_isup = isup;
	vsi->current_speed = new_speed;
	if (!isup) {
		netdev_info(vsi->netdev, "NIC Link is Down\n");
		return;
	}

	/* Warn user if link speed on NPAR enabled partition is not at
	 * least 10GB
	 */
	if (pf->hw.func_caps.npar_enable &&
	    (pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_1GB ||
	     pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_100MB))
		netdev_warn(vsi->netdev,
			    "The partition detected link speed that is less than 10Gbps\n");

	switch (pf->hw.phy.link_info.link_speed) {
	case I40E_LINK_SPEED_40GB:
		speed = "40 G";
		break;
	case I40E_LINK_SPEED_20GB:
		speed = "20 G";
		break;
	case I40E_LINK_SPEED_25GB:
		speed = "25 G";
		break;
	case I40E_LINK_SPEED_10GB:
		speed = "10 G";
		break;
	case I40E_LINK_SPEED_5GB:
		speed = "5 G";
		break;
	case I40E_LINK_SPEED_2_5GB:
		speed = "2.5 G";
		break;
	case I40E_LINK_SPEED_1GB:
		speed = "1000 M";
		break;
	case I40E_LINK_SPEED_100MB:
		speed = "100 M";
		break;
	default:
		break;
	}

	switch (pf->hw.fc.current_mode) {
	case I40E_FC_FULL:
		fc = "RX/TX";
		break;
	case I40E_FC_TX_PAUSE:
		fc = "TX";
		break;
	case I40E_FC_RX_PAUSE:
		fc = "RX";
		break;
	default:
		fc = "None";
		break;
	}

	if (pf->hw.phy.link_info.link_speed == I40E_LINK_SPEED_25GB) {
		req_fec = "None";
		fec = "None";
		an = "False";

		if (pf->hw.phy.link_info.an_info & I40E_AQ_AN_COMPLETED)
			an = "True";

		if (pf->hw.phy.link_info.fec_info &
		    I40E_AQ_CONFIG_FEC_KR_ENA)
			fec = "CL74 FC-FEC/BASE-R";
		else if (pf->hw.phy.link_info.fec_info &
			 I40E_AQ_CONFIG_FEC_RS_ENA)
			fec = "CL108 RS-FEC";

		/* 'CL108 RS-FEC' should be displayed when RS is requested, or
		 * both RS and FC are requested
		 */
		if (vsi->back->hw.phy.link_info.req_fec_info &
		    (I40E_AQ_REQUEST_FEC_KR | I40E_AQ_REQUEST_FEC_RS)) {
			if (vsi->back->hw.phy.link_info.req_fec_info &
			    I40E_AQ_REQUEST_FEC_RS)
				req_fec = "CL108 RS-FEC";
			else
				req_fec = "CL74 FC-FEC/BASE-R";
		}
		netdev_info(vsi->netdev,
			    "NIC Link is Up, %sbps Full Duplex, Requested FEC: %s, Negotiated FEC: %s, Autoneg: %s, Flow Control: %s\n",
			    speed, req_fec, fec, an, fc);
	} else {
		netdev_info(vsi->netdev,
			    "NIC Link is Up, %sbps Full Duplex, Flow Control: %s\n",
			    speed, fc);
	}

}