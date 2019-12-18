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
struct vlan_table {int dummy; } ;
struct ksz_device {int /*<<< orphan*/  vlan_cache; int /*<<< orphan*/  num_vlans; int /*<<< orphan*/  dev; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct ksz_device* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MULTICAST_STORM_DISABLE ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_0 ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_1 ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_5 ; 
 int /*<<< orphan*/  REG_SW_MAC_CTRL_6 ; 
 int /*<<< orphan*/  REG_SW_OPERATION ; 
 int /*<<< orphan*/  REG_SW_QM_CTRL__4 ; 
 int /*<<< orphan*/  SW_CHECK_LENGTH ; 
 int /*<<< orphan*/  SW_LEGAL_PACKET_DISABLE ; 
 int /*<<< orphan*/  SW_MIB_COUNTER_FREEZE ; 
 int /*<<< orphan*/  SW_OUT_RATE_LIMIT_QUEUE_BASED ; 
 int /*<<< orphan*/  SW_START ; 
 int /*<<< orphan*/  UNICAST_VLAN_BOUNDARY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz9477_cfg32 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz9477_config_cpu_port (struct dsa_switch*) ; 
 int ksz9477_reset_switch (struct ksz_device*) ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_init_mib_timer (struct ksz_device*) ; 

__attribute__((used)) static int ksz9477_setup(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	int ret = 0;

	dev->vlan_cache = devm_kcalloc(dev->dev, sizeof(struct vlan_table),
				       dev->num_vlans, GFP_KERNEL);
	if (!dev->vlan_cache)
		return -ENOMEM;

	ret = ksz9477_reset_switch(dev);
	if (ret) {
		dev_err(ds->dev, "failed to reset switch\n");
		return ret;
	}

	/* Required for port partitioning. */
	ksz9477_cfg32(dev, REG_SW_QM_CTRL__4, UNICAST_VLAN_BOUNDARY,
		      true);

	/* Do not work correctly with tail tagging. */
	ksz_cfg(dev, REG_SW_MAC_CTRL_0, SW_CHECK_LENGTH, false);

	/* accept packet up to 2000bytes */
	ksz_cfg(dev, REG_SW_MAC_CTRL_1, SW_LEGAL_PACKET_DISABLE, true);

	ksz9477_config_cpu_port(ds);

	ksz_cfg(dev, REG_SW_MAC_CTRL_1, MULTICAST_STORM_DISABLE, true);

	/* queue based egress rate limit */
	ksz_cfg(dev, REG_SW_MAC_CTRL_5, SW_OUT_RATE_LIMIT_QUEUE_BASED, true);

	/* enable global MIB counter freeze function */
	ksz_cfg(dev, REG_SW_MAC_CTRL_6, SW_MIB_COUNTER_FREEZE, true);

	/* start switch */
	ksz_cfg(dev, REG_SW_OPERATION, SW_START, true);

	ksz_init_mib_timer(dev);

	return 0;
}