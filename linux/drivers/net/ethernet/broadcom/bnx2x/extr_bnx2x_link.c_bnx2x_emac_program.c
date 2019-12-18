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
typedef  int u8 ;
typedef  int u16 ;
struct link_vars {int line_speed; scalar_t__ duplex; } ;
struct link_params {int port; struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int EMAC_MODE_25G_MODE ; 
 int EMAC_MODE_HALF_DUPLEX ; 
 int EMAC_MODE_PORT_GMII ; 
 int EMAC_MODE_PORT_MII ; 
 int EMAC_MODE_PORT_MII_10M ; 
 scalar_t__ EMAC_REG_EMAC_MODE ; 
 scalar_t__ GRCBASE_EMAC0 ; 
 int /*<<< orphan*/  LED_MODE_OPER ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_bits_en (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_set_led (struct link_params*,struct link_vars*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2x_emac_program(struct link_params *params,
			      struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;
	u8 port = params->port;
	u16 mode = 0;

	DP(NETIF_MSG_LINK, "setting link speed & duplex\n");
	bnx2x_bits_dis(bp, GRCBASE_EMAC0 + port*0x400 +
		       EMAC_REG_EMAC_MODE,
		       (EMAC_MODE_25G_MODE |
			EMAC_MODE_PORT_MII_10M |
			EMAC_MODE_HALF_DUPLEX));
	switch (vars->line_speed) {
	case SPEED_10:
		mode |= EMAC_MODE_PORT_MII_10M;
		break;

	case SPEED_100:
		mode |= EMAC_MODE_PORT_MII;
		break;

	case SPEED_1000:
		mode |= EMAC_MODE_PORT_GMII;
		break;

	case SPEED_2500:
		mode |= (EMAC_MODE_25G_MODE | EMAC_MODE_PORT_GMII);
		break;

	default:
		/* 10G not valid for EMAC */
		DP(NETIF_MSG_LINK, "Invalid line_speed 0x%x\n",
			   vars->line_speed);
		return -EINVAL;
	}

	if (vars->duplex == DUPLEX_HALF)
		mode |= EMAC_MODE_HALF_DUPLEX;
	bnx2x_bits_en(bp,
		      GRCBASE_EMAC0 + port*0x400 + EMAC_REG_EMAC_MODE,
		      mode);

	bnx2x_set_led(params, vars, LED_MODE_OPER, vars->line_speed);
	return 0;
}