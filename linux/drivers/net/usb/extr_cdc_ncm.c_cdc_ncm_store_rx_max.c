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
struct usbnet {scalar_t__* data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cdc_ncm_ctx {int /*<<< orphan*/  tx_max; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long cdc_ncm_check_rx_max (struct usbnet*,unsigned long) ; 
 int /*<<< orphan*/  cdc_ncm_update_rxtx_max (struct usbnet*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct usbnet* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t cdc_ncm_store_rx_max(struct device *d,  struct device_attribute *attr, const char *buf, size_t len)
{
	struct usbnet *dev = netdev_priv(to_net_dev(d));
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	unsigned long val;

	if (kstrtoul(buf, 0, &val) || cdc_ncm_check_rx_max(dev, val) != val)
		return -EINVAL;

	cdc_ncm_update_rxtx_max(dev, val, ctx->tx_max);
	return len;
}