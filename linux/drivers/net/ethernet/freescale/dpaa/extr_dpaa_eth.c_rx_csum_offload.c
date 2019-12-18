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
typedef  int /*<<< orphan*/  u8 ;
struct qm_fd {int /*<<< orphan*/  status; } ;
struct dpaa_priv {TYPE_1__* net_dev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int FM_FD_STAT_L4CV ; 
 int NETIF_F_RXCSUM ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 rx_csum_offload(const struct dpaa_priv *priv, const struct qm_fd *fd)
{
	/* The parser has run and performed L4 checksum validation.
	 * We know there were no parser errors (and implicitly no
	 * L4 csum error), otherwise we wouldn't be here.
	 */
	if ((priv->net_dev->features & NETIF_F_RXCSUM) &&
	    (be32_to_cpu(fd->status) & FM_FD_STAT_L4CV))
		return CHECKSUM_UNNECESSARY;

	/* We're here because either the parser didn't run or the L4 checksum
	 * was not verified. This may include the case of a UDP frame with
	 * checksum zero or an L4 proto other than TCP/UDP
	 */
	return CHECKSUM_NONE;
}