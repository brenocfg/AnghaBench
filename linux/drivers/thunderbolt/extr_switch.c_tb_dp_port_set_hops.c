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
typedef  unsigned int u32 ;
struct tb_port {int /*<<< orphan*/  cap_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  TB_CFG_PORT ; 
 unsigned int TB_DP_AUX_RX_HOPID_MASK ; 
 unsigned int TB_DP_AUX_RX_HOPID_SHIFT ; 
 unsigned int TB_DP_AUX_TX_HOPID_MASK ; 
 unsigned int TB_DP_VIDEO_HOPID_MASK ; 
 unsigned int TB_DP_VIDEO_HOPID_SHIFT ; 
 int tb_port_read (struct tb_port*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tb_port_write (struct tb_port*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tb_dp_port_set_hops(struct tb_port *port, unsigned int video,
			unsigned int aux_tx, unsigned int aux_rx)
{
	u32 data[2];
	int ret;

	ret = tb_port_read(port, data, TB_CFG_PORT, port->cap_adap,
			   ARRAY_SIZE(data));
	if (ret)
		return ret;

	data[0] &= ~TB_DP_VIDEO_HOPID_MASK;
	data[1] &= ~(TB_DP_AUX_RX_HOPID_MASK | TB_DP_AUX_TX_HOPID_MASK);

	data[0] |= (video << TB_DP_VIDEO_HOPID_SHIFT) & TB_DP_VIDEO_HOPID_MASK;
	data[1] |= aux_tx & TB_DP_AUX_TX_HOPID_MASK;
	data[1] |= (aux_rx << TB_DP_AUX_RX_HOPID_SHIFT) & TB_DP_AUX_RX_HOPID_MASK;

	return tb_port_write(port, data, TB_CFG_PORT, port->cap_adap,
			     ARRAY_SIZE(data));
}