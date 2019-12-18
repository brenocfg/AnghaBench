#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ autoneg; int speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct TYPE_8__ {int is_autoneg; int link_speed_msk; TYPE_2__* aq_hw_caps; } ;
struct aq_nic_s {TYPE_4__ aq_nic_cfg; int /*<<< orphan*/  fwreq_mutex; int /*<<< orphan*/  aq_hw; TYPE_3__* aq_fw_ops; } ;
struct TYPE_7__ {int (* set_link_speed ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {int link_speed_msk; } ;

/* Variables and functions */
 int AQ_NIC_RATE_100M ; 
 int AQ_NIC_RATE_10G ; 
 int AQ_NIC_RATE_1G ; 
 int AQ_NIC_RATE_2GS ; 
 int AQ_NIC_RATE_5G ; 
 scalar_t__ AUTONEG_ENABLE ; 
#define  SPEED_100 132 
#define  SPEED_1000 131 
#define  SPEED_10000 130 
#define  SPEED_2500 129 
#define  SPEED_5000 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int aq_nic_set_link_ksettings(struct aq_nic_s *self,
			      const struct ethtool_link_ksettings *cmd)
{
	u32 speed = 0U;
	u32 rate = 0U;
	int err = 0;

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		rate = self->aq_nic_cfg.aq_hw_caps->link_speed_msk;
		self->aq_nic_cfg.is_autoneg = true;
	} else {
		speed = cmd->base.speed;

		switch (speed) {
		case SPEED_100:
			rate = AQ_NIC_RATE_100M;
			break;

		case SPEED_1000:
			rate = AQ_NIC_RATE_1G;
			break;

		case SPEED_2500:
			rate = AQ_NIC_RATE_2GS;
			break;

		case SPEED_5000:
			rate = AQ_NIC_RATE_5G;
			break;

		case SPEED_10000:
			rate = AQ_NIC_RATE_10G;
			break;

		default:
			err = -1;
			goto err_exit;
		break;
		}
		if (!(self->aq_nic_cfg.aq_hw_caps->link_speed_msk & rate)) {
			err = -1;
			goto err_exit;
		}

		self->aq_nic_cfg.is_autoneg = false;
	}

	mutex_lock(&self->fwreq_mutex);
	err = self->aq_fw_ops->set_link_speed(self->aq_hw, rate);
	mutex_unlock(&self->fwreq_mutex);
	if (err < 0)
		goto err_exit;

	self->aq_nic_cfg.link_speed_msk = rate;

err_exit:
	return err;
}