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
struct ksz_port {int on; int phy; int fiber; int /*<<< orphan*/  member; int /*<<< orphan*/  vid_member; } ;
struct ksz_device {int port_cnt; size_t cpu_port; int phy_port_cnt; struct ksz_port* ports; int /*<<< orphan*/  port_mask; int /*<<< orphan*/  host_mask; int /*<<< orphan*/  member; } ;
struct dsa_switch {int num_ports; struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 int PORT_FIBER_MODE ; 
 int /*<<< orphan*/  PORT_FORCE_FLOW_CTRL ; 
 int /*<<< orphan*/  P_REMOTE_STATUS ; 
 int /*<<< orphan*/  P_STP_CTRL ; 
 int /*<<< orphan*/  REG_SW_CTRL_2 ; 
 int SWITCH_PORT_NUM ; 
 int /*<<< orphan*/  SW_LEGAL_PACKET_DISABLE ; 
 int /*<<< orphan*/  SW_TAIL_TAG_ENABLE ; 
 int /*<<< orphan*/  S_TAIL_TAG_CTRL ; 
 int /*<<< orphan*/  ksz8795_port_setup (struct ksz_device*,size_t,int) ; 
 int /*<<< orphan*/  ksz8795_port_stp_state_set (struct dsa_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ksz8795_config_cpu_port(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	struct ksz_port *p;
	u8 remote;
	int i;

	ds->num_ports = dev->port_cnt + 1;

	/* Switch marks the maximum frame with extra byte as oversize. */
	ksz_cfg(dev, REG_SW_CTRL_2, SW_LEGAL_PACKET_DISABLE, true);
	ksz_cfg(dev, S_TAIL_TAG_CTRL, SW_TAIL_TAG_ENABLE, true);

	p = &dev->ports[dev->cpu_port];
	p->vid_member = dev->port_mask;
	p->on = 1;

	ksz8795_port_setup(dev, dev->cpu_port, true);
	dev->member = dev->host_mask;

	for (i = 0; i < SWITCH_PORT_NUM; i++) {
		p = &dev->ports[i];

		/* Initialize to non-zero so that ksz_cfg_port_member() will
		 * be called.
		 */
		p->vid_member = BIT(i);
		p->member = dev->port_mask;
		ksz8795_port_stp_state_set(ds, i, BR_STATE_DISABLED);

		/* Last port may be disabled. */
		if (i == dev->port_cnt)
			break;
		p->on = 1;
		p->phy = 1;
	}
	for (i = 0; i < dev->phy_port_cnt; i++) {
		p = &dev->ports[i];
		if (!p->on)
			continue;
		ksz_pread8(dev, i, P_REMOTE_STATUS, &remote);
		if (remote & PORT_FIBER_MODE)
			p->fiber = 1;
		if (p->fiber)
			ksz_port_cfg(dev, i, P_STP_CTRL, PORT_FORCE_FLOW_CTRL,
				     true);
		else
			ksz_port_cfg(dev, i, P_STP_CTRL, PORT_FORCE_FLOW_CTRL,
				     false);
	}
}