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
struct r8192_priv {int /*<<< orphan*/  wx_mutex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int _rtl92e_try_up (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static int _rtl92e_open(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	int ret;

	mutex_lock(&priv->wx_mutex);
	ret = _rtl92e_try_up(dev);
	mutex_unlock(&priv->wx_mutex);
	return ret;

}