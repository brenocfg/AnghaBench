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
struct r8192_priv {int /*<<< orphan*/  rfpath_check_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl92e_dm_check_rx_path_selection(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	schedule_delayed_work(&priv->rfpath_check_wq, 0);
}