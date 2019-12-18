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
struct usbnet {int /*<<< orphan*/  net; scalar_t__* data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cdc_ncm_ctx {int drvflags; int /*<<< orphan*/  mtx; scalar_t__ delayed_ndp16; int /*<<< orphan*/  max_ndp_size; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int CDC_NCM_FLAG_NDP_TO_END ; 
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 
 int /*<<< orphan*/  usbnet_start_xmit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ndp_to_end_store(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	bool enable;

	if (strtobool(buf, &enable))
		return -EINVAL;

	/* no change? */
	if (enable == (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		return len;

	if (enable && !ctx->delayed_ndp16) {
		ctx->delayed_ndp16 = kzalloc(ctx->max_ndp_size, GFP_KERNEL);
		if (!ctx->delayed_ndp16)
			return -ENOMEM;
	}

	/* flush pending data before changing flag */
	netif_tx_lock_bh(dev->net);
	usbnet_start_xmit(NULL, dev->net);
	spin_lock_bh(&ctx->mtx);
	if (enable)
		ctx->drvflags |= CDC_NCM_FLAG_NDP_TO_END;
	else
		ctx->drvflags &= ~CDC_NCM_FLAG_NDP_TO_END;
	spin_unlock_bh(&ctx->mtx);
	netif_tx_unlock_bh(dev->net);

	return len;
}