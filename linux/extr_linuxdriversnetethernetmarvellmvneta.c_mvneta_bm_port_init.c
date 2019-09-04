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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mvneta_port {int id; TYPE_2__* pool_short; TYPE_4__* pool_long; int /*<<< orphan*/  bm_priv; TYPE_3__* dev; int /*<<< orphan*/  neta_armada3700; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int port_map; int /*<<< orphan*/  id; int /*<<< orphan*/  buf_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_6__ {int port_map; int /*<<< orphan*/  id; int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MVNETA_BM_LONG ; 
 int /*<<< orphan*/  MVNETA_BM_SHORT ; 
 int /*<<< orphan*/  MVNETA_BM_SHORT_PKT_SIZE ; 
 int /*<<< orphan*/  MVNETA_RX_PKT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_bufsize_set (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_destroy (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 void* mvneta_bm_pool_use (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mvneta_bm_port_mbus_init (struct mvneta_port*) ; 
 int /*<<< orphan*/  netdev_info (TYPE_3__*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int mvneta_bm_port_init(struct platform_device *pdev,
			       struct mvneta_port *pp)
{
	struct device_node *dn = pdev->dev.of_node;
	u32 long_pool_id, short_pool_id;

	if (!pp->neta_armada3700) {
		int ret;

		ret = mvneta_bm_port_mbus_init(pp);
		if (ret)
			return ret;
	}

	if (of_property_read_u32(dn, "bm,pool-long", &long_pool_id)) {
		netdev_info(pp->dev, "missing long pool id\n");
		return -EINVAL;
	}

	/* Create port's long pool depending on mtu */
	pp->pool_long = mvneta_bm_pool_use(pp->bm_priv, long_pool_id,
					   MVNETA_BM_LONG, pp->id,
					   MVNETA_RX_PKT_SIZE(pp->dev->mtu));
	if (!pp->pool_long) {
		netdev_info(pp->dev, "fail to obtain long pool for port\n");
		return -ENOMEM;
	}

	pp->pool_long->port_map |= 1 << pp->id;

	mvneta_bm_pool_bufsize_set(pp, pp->pool_long->buf_size,
				   pp->pool_long->id);

	/* If short pool id is not defined, assume using single pool */
	if (of_property_read_u32(dn, "bm,pool-short", &short_pool_id))
		short_pool_id = long_pool_id;

	/* Create port's short pool */
	pp->pool_short = mvneta_bm_pool_use(pp->bm_priv, short_pool_id,
					    MVNETA_BM_SHORT, pp->id,
					    MVNETA_BM_SHORT_PKT_SIZE);
	if (!pp->pool_short) {
		netdev_info(pp->dev, "fail to obtain short pool for port\n");
		mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_long, 1 << pp->id);
		return -ENOMEM;
	}

	if (short_pool_id != long_pool_id) {
		pp->pool_short->port_map |= 1 << pp->id;
		mvneta_bm_pool_bufsize_set(pp, pp->pool_short->buf_size,
					   pp->pool_short->id);
	}

	return 0;
}