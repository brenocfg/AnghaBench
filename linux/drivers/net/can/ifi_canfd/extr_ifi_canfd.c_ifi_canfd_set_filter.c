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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ifi_canfd_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IFI_CANFD_FILTER_IDENT (int /*<<< orphan*/  const) ; 
 scalar_t__ IFI_CANFD_FILTER_MASK (int /*<<< orphan*/  const) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/  const,scalar_t__) ; 

__attribute__((used)) static void ifi_canfd_set_filter(struct net_device *ndev, const u32 id,
				 const u32 mask, const u32 ident)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);

	writel(mask, priv->base + IFI_CANFD_FILTER_MASK(id));
	writel(ident, priv->base + IFI_CANFD_FILTER_IDENT(id));
}