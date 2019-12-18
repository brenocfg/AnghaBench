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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx4_vhcr {int dummy; } ;
struct TYPE_2__ {int num_ports; scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct mlx4_cmd_info {int dummy; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int DEV_CAP_EXT_2_FLAG_80_VFS ; 
 int DEV_CAP_EXT_2_FLAG_FSM ; 
 int DEV_CAP_EXT_2_FLAG_PFC_COUNTERS ; 
 int DEV_CAP_EXT_2_FLAG_VLAN_CONTROL ; 
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_DEV_CAP ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV ; 
 int MLX4_DEV_CAP_FLAG_RSS_IP_FRAG ; 
 int MLX4_DEV_CAP_FLAG_WOL_PORT1 ; 
 int MLX4_FLAG_PORT_REMAP ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BF_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_BMME_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CONFIG_DEV_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_ECN_QCN_VER_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_EXT_FLAGS_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_PORT_BEACON_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_QP_RATE_LIMIT_NUM_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_VL_PORT_OFFSET ; 
 int /*<<< orphan*/  QUERY_DEV_CAP_VXLAN ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_unsupported_roce_caps (int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 

int mlx4_QUERY_DEV_CAP_wrapper(struct mlx4_dev *dev, int slave,
			       struct mlx4_vhcr *vhcr,
			       struct mlx4_cmd_mailbox *inbox,
			       struct mlx4_cmd_mailbox *outbox,
			       struct mlx4_cmd_info *cmd)
{
	u64	flags;
	int	err = 0;
	u8	field;
	u16	field16;
	u32	bmme_flags, field32;
	int	real_port;
	int	slave_port;
	int	first_port;
	struct mlx4_active_ports actv_ports;

	err = mlx4_cmd_box(dev, 0, outbox->dma, 0, 0, MLX4_CMD_QUERY_DEV_CAP,
			   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	if (err)
		return err;

	disable_unsupported_roce_caps(outbox->buf);
	/* add port mng change event capability and disable mw type 1
	 * unconditionally to slaves
	 */
	MLX4_GET(flags, outbox->buf, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);
	flags |= MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV;
	flags &= ~MLX4_DEV_CAP_FLAG_MEM_WINDOW;
	actv_ports = mlx4_get_active_ports(dev, slave);
	first_port = find_first_bit(actv_ports.ports, dev->caps.num_ports);
	for (slave_port = 0, real_port = first_port;
	     real_port < first_port +
	     bitmap_weight(actv_ports.ports, dev->caps.num_ports);
	     ++real_port, ++slave_port) {
		if (flags & (MLX4_DEV_CAP_FLAG_WOL_PORT1 << real_port))
			flags |= MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port;
		else
			flags &= ~(MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port);
	}
	for (; slave_port < dev->caps.num_ports; ++slave_port)
		flags &= ~(MLX4_DEV_CAP_FLAG_WOL_PORT1 << slave_port);

	/* Not exposing RSS IP fragments to guests */
	flags &= ~MLX4_DEV_CAP_FLAG_RSS_IP_FRAG;
	MLX4_PUT(outbox->buf, flags, QUERY_DEV_CAP_EXT_FLAGS_OFFSET);

	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_VL_PORT_OFFSET);
	field &= ~0x0F;
	field |= bitmap_weight(actv_ports.ports, dev->caps.num_ports) & 0x0F;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_VL_PORT_OFFSET);

	/* For guests, disable timestamp */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CQ_TS_SUPPORT_OFFSET);

	/* For guests, disable vxlan tunneling and QoS support */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_VXLAN);
	field &= 0xd7;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_VXLAN);

	/* For guests, disable port BEACON */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_PORT_BEACON_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_PORT_BEACON_OFFSET);

	/* For guests, report Blueflame disabled */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_BF_OFFSET);
	field &= 0x7f;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_BF_OFFSET);

	/* For guests, disable mw type 2 and port remap*/
	MLX4_GET(bmme_flags, outbox->buf, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);
	bmme_flags &= ~MLX4_BMME_FLAG_TYPE_2_WIN;
	bmme_flags &= ~MLX4_FLAG_PORT_REMAP;
	MLX4_PUT(outbox->buf, bmme_flags, QUERY_DEV_CAP_BMME_FLAGS_OFFSET);

	/* turn off device-managed steering capability if not enabled */
	if (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED) {
		MLX4_GET(field, outbox->buf,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
		field &= 0x7f;
		MLX4_PUT(outbox->buf, field,
			 QUERY_DEV_CAP_FLOW_STEERING_RANGE_EN_OFFSET);
	}

	/* turn off ipoib managed steering for guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET);
	field &= ~0x80;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_FLOW_STEERING_IPOIB_OFFSET);

	/* turn off host side virt features (VST, FSM, etc) for guests */
	MLX4_GET(field32, outbox->buf, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);
	field32 &= ~(DEV_CAP_EXT_2_FLAG_VLAN_CONTROL | DEV_CAP_EXT_2_FLAG_80_VFS |
		     DEV_CAP_EXT_2_FLAG_FSM | DEV_CAP_EXT_2_FLAG_PFC_COUNTERS);
	MLX4_PUT(outbox->buf, field32, QUERY_DEV_CAP_EXT_2_FLAGS_OFFSET);

	/* turn off QCN for guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_ECN_QCN_VER_OFFSET);
	field &= 0xfe;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_ECN_QCN_VER_OFFSET);

	/* turn off QP max-rate limiting for guests */
	field16 = 0;
	MLX4_PUT(outbox->buf, field16, QUERY_DEV_CAP_QP_RATE_LIMIT_NUM_OFFSET);

	/* turn off QoS per VF support for guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE);
	field &= 0xef;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CQ_EQ_CACHE_LINE_STRIDE);

	/* turn off ignore FCS feature for guests */
	MLX4_GET(field, outbox->buf, QUERY_DEV_CAP_CONFIG_DEV_OFFSET);
	field &= 0xfb;
	MLX4_PUT(outbox->buf, field, QUERY_DEV_CAP_CONFIG_DEV_OFFSET);

	return 0;
}