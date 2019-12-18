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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct hwrm_port_led_cfg_input {int num_leds; int /*<<< orphan*/  enables; int /*<<< orphan*/  led0_id; void* port_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_pf_info {int port_id; } ;
struct bnxt_led_cfg {int /*<<< orphan*/  led_group_id; void* led_blink_off; void* led_blink_on; int /*<<< orphan*/  led_state; int /*<<< orphan*/  led_id; } ;
struct bnxt {int num_leds; TYPE_1__* leds; struct bnxt_pf_info pf; } ;
typedef  int /*<<< orphan*/  req ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
typedef  void* __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  led_group_id; int /*<<< orphan*/  led_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_LED_DFLT_ENABLES (int) ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ETHTOOL_ID_ACTIVE ; 
 int ETHTOOL_ID_INACTIVE ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PORT_LED_CFG ; 
 int /*<<< orphan*/  PORT_LED_CFG_REQ_LED0_STATE_BLINKALT ; 
 int /*<<< orphan*/  PORT_LED_CFG_REQ_LED1_STATE_DEFAULT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_port_led_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_port_led_cfg_input*,int,int /*<<< orphan*/ ) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_set_phys_id(struct net_device *dev,
			    enum ethtool_phys_id_state state)
{
	struct hwrm_port_led_cfg_input req = {0};
	struct bnxt *bp = netdev_priv(dev);
	struct bnxt_pf_info *pf = &bp->pf;
	struct bnxt_led_cfg *led_cfg;
	u8 led_state;
	__le16 duration;
	int i, rc;

	if (!bp->num_leds || BNXT_VF(bp))
		return -EOPNOTSUPP;

	if (state == ETHTOOL_ID_ACTIVE) {
		led_state = PORT_LED_CFG_REQ_LED0_STATE_BLINKALT;
		duration = cpu_to_le16(500);
	} else if (state == ETHTOOL_ID_INACTIVE) {
		led_state = PORT_LED_CFG_REQ_LED1_STATE_DEFAULT;
		duration = cpu_to_le16(0);
	} else {
		return -EINVAL;
	}
	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PORT_LED_CFG, -1, -1);
	req.port_id = cpu_to_le16(pf->port_id);
	req.num_leds = bp->num_leds;
	led_cfg = (struct bnxt_led_cfg *)&req.led0_id;
	for (i = 0; i < bp->num_leds; i++, led_cfg++) {
		req.enables |= BNXT_LED_DFLT_ENABLES(i);
		led_cfg->led_id = bp->leds[i].led_id;
		led_cfg->led_state = led_state;
		led_cfg->led_blink_on = duration;
		led_cfg->led_blink_off = duration;
		led_cfg->led_group_id = bp->leds[i].led_group_id;
	}
	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}