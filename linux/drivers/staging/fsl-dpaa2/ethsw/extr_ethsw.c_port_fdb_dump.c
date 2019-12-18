#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct netlink_callback {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct fdb_dump_entry {int dummy; } ;
struct ethsw_port_priv {struct ethsw_core* ethsw_data; } ;
struct ethsw_dump_ctx {int idx; struct netlink_callback* cb; struct sk_buff* skb; struct net_device* dev; } ;
struct TYPE_4__ {int max_fdb_entries; } ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; TYPE_2__ sw_attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  fdb_entry ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int dpsw_fdb_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int ethsw_fdb_do_dump (struct fdb_dump_entry*,struct ethsw_dump_ctx*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  port_fdb_valid_entry (struct fdb_dump_entry*,struct ethsw_port_priv*) ; 

__attribute__((used)) static int port_fdb_dump(struct sk_buff *skb, struct netlink_callback *cb,
			 struct net_device *net_dev,
			 struct net_device *filter_dev, int *idx)
{
	struct ethsw_port_priv *port_priv = netdev_priv(net_dev);
	struct ethsw_core *ethsw = port_priv->ethsw_data;
	struct device *dev = net_dev->dev.parent;
	struct fdb_dump_entry *fdb_entries;
	struct fdb_dump_entry fdb_entry;
	struct ethsw_dump_ctx dump = {
		.dev = net_dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	};
	dma_addr_t fdb_dump_iova;
	u16 num_fdb_entries;
	u32 fdb_dump_size;
	int err = 0, i;
	u8 *dma_mem;

	fdb_dump_size = ethsw->sw_attr.max_fdb_entries * sizeof(fdb_entry);
	dma_mem = kzalloc(fdb_dump_size, GFP_KERNEL);
	if (!dma_mem)
		return -ENOMEM;

	fdb_dump_iova = dma_map_single(dev, dma_mem, fdb_dump_size,
				       DMA_FROM_DEVICE);
	if (dma_mapping_error(dev, fdb_dump_iova)) {
		netdev_err(net_dev, "dma_map_single() failed\n");
		err = -ENOMEM;
		goto err_map;
	}

	err = dpsw_fdb_dump(ethsw->mc_io, 0, ethsw->dpsw_handle, 0,
			    fdb_dump_iova, fdb_dump_size, &num_fdb_entries);
	if (err) {
		netdev_err(net_dev, "dpsw_fdb_dump() = %d\n", err);
		goto err_dump;
	}

	dma_unmap_single(dev, fdb_dump_iova, fdb_dump_size, DMA_FROM_DEVICE);

	fdb_entries = (struct fdb_dump_entry *)dma_mem;
	for (i = 0; i < num_fdb_entries; i++) {
		fdb_entry = fdb_entries[i];

		if (!port_fdb_valid_entry(&fdb_entry, port_priv))
			continue;

		err = ethsw_fdb_do_dump(&fdb_entry, &dump);
		if (err)
			goto end;
	}

end:
	*idx = dump.idx;

	kfree(dma_mem);

	return 0;

err_dump:
	dma_unmap_single(dev, fdb_dump_iova, fdb_dump_size, DMA_TO_DEVICE);
err_map:
	kfree(dma_mem);
	return err;
}