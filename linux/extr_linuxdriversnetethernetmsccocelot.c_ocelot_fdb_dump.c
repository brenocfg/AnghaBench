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
struct sk_buff {int dummy; } ;
struct ocelot_port {int dummy; } ;
struct ocelot_mact_entry {int dummy; } ;
struct ocelot_dump_ctx {int idx; struct netlink_callback* cb; struct sk_buff* skb; struct net_device* dev; } ;
struct netlink_callback {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int ocelot_fdb_do_dump (struct ocelot_mact_entry*,struct ocelot_dump_ctx*) ; 
 int ocelot_mact_read (struct ocelot_port*,int,int,struct ocelot_mact_entry*) ; 

__attribute__((used)) static int ocelot_fdb_dump(struct sk_buff *skb, struct netlink_callback *cb,
			   struct net_device *dev,
			   struct net_device *filter_dev, int *idx)
{
	struct ocelot_port *port = netdev_priv(dev);
	int i, j, ret = 0;
	struct ocelot_dump_ctx dump = {
		.dev = dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	};

	struct ocelot_mact_entry entry;

	/* Loop through all the mac tables entries. There are 1024 rows of 4
	 * entries.
	 */
	for (i = 0; i < 1024; i++) {
		for (j = 0; j < 4; j++) {
			ret = ocelot_mact_read(port, i, j, &entry);
			/* If the entry is invalid (wrong port, invalid...),
			 * skip it.
			 */
			if (ret == -EINVAL)
				continue;
			else if (ret)
				goto end;

			ret = ocelot_fdb_do_dump(&entry, &dump);
			if (ret)
				goto end;
		}
	}

end:
	*idx = dump.idx;
	return ret;
}