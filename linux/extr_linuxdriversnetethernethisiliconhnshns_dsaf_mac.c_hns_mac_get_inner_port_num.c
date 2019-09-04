#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hns_mac_cb {int mac_id; TYPE_3__* dsaf_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int dsaf_mode; TYPE_2__ ae_dev; TYPE_1__** rcb_common; } ;
struct TYPE_4__ {int max_vfn; int max_q_per_vf; } ;

/* Variables and functions */
 scalar_t__ DSAF_BASE_INNER_PORT_NUM ; 
 int DSAF_MAX_PORT_NUM ; 
#define  DSAF_MODE_DISABLE_2PORT_16VM 141 
#define  DSAF_MODE_DISABLE_2PORT_64VM 140 
#define  DSAF_MODE_DISABLE_2PORT_8VM 139 
#define  DSAF_MODE_DISABLE_6PORT_0VM 138 
#define  DSAF_MODE_DISABLE_6PORT_16VM 137 
#define  DSAF_MODE_DISABLE_6PORT_2VM 136 
#define  DSAF_MODE_DISABLE_6PORT_4VM 135 
#define  DSAF_MODE_DISABLE_FIX 134 
 int DSAF_MODE_ENABLE ; 
#define  DSAF_MODE_ENABLE_0VM 133 
#define  DSAF_MODE_ENABLE_128VM 132 
#define  DSAF_MODE_ENABLE_16VM 131 
#define  DSAF_MODE_ENABLE_32VM 130 
#define  DSAF_MODE_ENABLE_8VM 129 
#define  DSAF_MODE_ENABLE_FIX 128 
 int DSAF_MODE_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 

int hns_mac_get_inner_port_num(struct hns_mac_cb *mac_cb, u8 vmid, u8 *port_num)
{
	int q_num_per_vf, vf_num_per_port;
	int vm_queue_id;
	u8 tmp_port;

	if (mac_cb->dsaf_dev->dsaf_mode <= DSAF_MODE_ENABLE) {
		if (mac_cb->mac_id != DSAF_MAX_PORT_NUM) {
			dev_err(mac_cb->dev,
				"input invalid, %s mac%d vmid%d !\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, vmid);
			return -EINVAL;
		}
	} else if (mac_cb->dsaf_dev->dsaf_mode < DSAF_MODE_MAX) {
		if (mac_cb->mac_id >= DSAF_MAX_PORT_NUM) {
			dev_err(mac_cb->dev,
				"input invalid, %s mac%d vmid%d!\n",
				mac_cb->dsaf_dev->ae_dev.name,
				mac_cb->mac_id, vmid);
			return -EINVAL;
		}
	} else {
		dev_err(mac_cb->dev, "dsaf mode invalid, %s mac%d!\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id);
		return -EINVAL;
	}

	if (vmid >= mac_cb->dsaf_dev->rcb_common[0]->max_vfn) {
		dev_err(mac_cb->dev, "input invalid, %s mac%d vmid%d !\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id, vmid);
		return -EINVAL;
	}

	q_num_per_vf = mac_cb->dsaf_dev->rcb_common[0]->max_q_per_vf;
	vf_num_per_port = mac_cb->dsaf_dev->rcb_common[0]->max_vfn;

	vm_queue_id = vmid * q_num_per_vf +
			vf_num_per_port * q_num_per_vf * mac_cb->mac_id;

	switch (mac_cb->dsaf_dev->dsaf_mode) {
	case DSAF_MODE_ENABLE_FIX:
		tmp_port = 0;
		break;
	case DSAF_MODE_DISABLE_FIX:
		tmp_port = 0;
		break;
	case DSAF_MODE_ENABLE_0VM:
	case DSAF_MODE_ENABLE_8VM:
	case DSAF_MODE_ENABLE_16VM:
	case DSAF_MODE_ENABLE_32VM:
	case DSAF_MODE_ENABLE_128VM:
	case DSAF_MODE_DISABLE_2PORT_8VM:
	case DSAF_MODE_DISABLE_2PORT_16VM:
	case DSAF_MODE_DISABLE_2PORT_64VM:
	case DSAF_MODE_DISABLE_6PORT_0VM:
	case DSAF_MODE_DISABLE_6PORT_2VM:
	case DSAF_MODE_DISABLE_6PORT_4VM:
	case DSAF_MODE_DISABLE_6PORT_16VM:
		tmp_port = vm_queue_id;
		break;
	default:
		dev_err(mac_cb->dev, "dsaf mode invalid, %s mac%d!\n",
			mac_cb->dsaf_dev->ae_dev.name, mac_cb->mac_id);
		return -EINVAL;
	}
	tmp_port += DSAF_BASE_INNER_PORT_NUM;

	*port_num = tmp_port;

	return 0;
}