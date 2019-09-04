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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_CM ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* to_net_dev (struct device*) ; 

__attribute__((used)) static ssize_t show_mode(struct device *d, struct device_attribute *attr,
			 char *buf)
{
	struct net_device *dev = to_net_dev(d);
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	if (test_bit(IPOIB_FLAG_ADMIN_CM, &priv->flags))
		return sprintf(buf, "connected\n");
	else
		return sprintf(buf, "datagram\n");
}