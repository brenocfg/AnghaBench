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
typedef  int /*<<< orphan*/  u32 ;
struct qm_fd {int /*<<< orphan*/  status; } ;
struct net_device {int dummy; } ;
struct dpaa_priv {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  phe; int /*<<< orphan*/  fse; int /*<<< orphan*/  fpe; int /*<<< orphan*/  dme; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_errors; } ;
struct dpaa_percpu_priv {TYPE_2__ rx_errors; TYPE_1__ stats; } ;

/* Variables and functions */
 int FM_FD_ERR_DMA ; 
 int FM_FD_ERR_PHYSICAL ; 
 int FM_FD_ERR_PRS_HDR_ERR ; 
 int FM_FD_ERR_SIZE ; 
 int FM_FD_STAT_RX_ERRORS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa_fd_release (struct net_device*,struct qm_fd const*) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct dpaa_priv const*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static void dpaa_rx_error(struct net_device *net_dev,
			  const struct dpaa_priv *priv,
			  struct dpaa_percpu_priv *percpu_priv,
			  const struct qm_fd *fd,
			  u32 fqid)
{
	if (net_ratelimit())
		netif_err(priv, hw, net_dev, "Err FD status = 0x%08x\n",
			  be32_to_cpu(fd->status) & FM_FD_STAT_RX_ERRORS);

	percpu_priv->stats.rx_errors++;

	if (be32_to_cpu(fd->status) & FM_FD_ERR_DMA)
		percpu_priv->rx_errors.dme++;
	if (be32_to_cpu(fd->status) & FM_FD_ERR_PHYSICAL)
		percpu_priv->rx_errors.fpe++;
	if (be32_to_cpu(fd->status) & FM_FD_ERR_SIZE)
		percpu_priv->rx_errors.fse++;
	if (be32_to_cpu(fd->status) & FM_FD_ERR_PRS_HDR_ERR)
		percpu_priv->rx_errors.phe++;

	dpaa_fd_release(net_dev, fd);
}