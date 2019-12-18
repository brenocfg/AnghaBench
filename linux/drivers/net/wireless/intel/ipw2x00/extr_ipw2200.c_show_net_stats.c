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
struct ipw_priv {int config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int CFG_NET_STATS ; 
 struct ipw_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static ssize_t show_net_stats(struct device *d, struct device_attribute *attr,
			      char *buf)
{
	struct ipw_priv *priv = dev_get_drvdata(d);
	return sprintf(buf, "%c\n", (priv->config & CFG_NET_STATS) ? '1' : '0');
}