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
typedef  size_t u16 ;
struct TYPE_4__ {size_t abs_id; } ;
struct sge_eth_rxq {TYPE_2__ rspq; } ;
struct port_info {size_t first_qset; int rss_size; int /*<<< orphan*/  viid; struct adapter* adapter; } ;
struct TYPE_3__ {struct sge_eth_rxq* ethrxq; } ;
struct adapter {int /*<<< orphan*/  mbox; int /*<<< orphan*/  pf; TYPE_1__ sge; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F ; 
 int FW_RSS_VI_CONFIG_CMD_UDPEN_F ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (size_t*) ; 
 size_t* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int t4_config_rss_range (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t*,int) ; 
 int t4_config_vi_rss (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 

int cxgb4_write_rss(const struct port_info *pi, const u16 *queues)
{
	u16 *rss;
	int i, err;
	struct adapter *adapter = pi->adapter;
	const struct sge_eth_rxq *rxq;

	rxq = &adapter->sge.ethrxq[pi->first_qset];
	rss = kmalloc_array(pi->rss_size, sizeof(u16), GFP_KERNEL);
	if (!rss)
		return -ENOMEM;

	/* map the queue indices to queue ids */
	for (i = 0; i < pi->rss_size; i++, queues++)
		rss[i] = rxq[*queues].rspq.abs_id;

	err = t4_config_rss_range(adapter, adapter->pf, pi->viid, 0,
				  pi->rss_size, rss, pi->rss_size);
	/* If Tunnel All Lookup isn't specified in the global RSS
	 * Configuration, then we need to specify a default Ingress
	 * Queue for any ingress packets which aren't hashed.  We'll
	 * use our first ingress queue ...
	 */
	if (!err)
		err = t4_config_vi_rss(adapter, adapter->mbox, pi->viid,
				       FW_RSS_VI_CONFIG_CMD_IP6FOURTUPEN_F |
				       FW_RSS_VI_CONFIG_CMD_IP6TWOTUPEN_F |
				       FW_RSS_VI_CONFIG_CMD_IP4FOURTUPEN_F |
				       FW_RSS_VI_CONFIG_CMD_IP4TWOTUPEN_F |
				       FW_RSS_VI_CONFIG_CMD_UDPEN_F,
				       rss[0]);
	kfree(rss);
	return err;
}