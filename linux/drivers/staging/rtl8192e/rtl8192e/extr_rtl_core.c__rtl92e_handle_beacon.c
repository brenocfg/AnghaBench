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
struct rtllib_network {int dummy; } ;
struct rtllib_beacon {int dummy; } ;
struct r8192_priv {int /*<<< orphan*/  update_beacon_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92e_qos_handle_probe_response (struct r8192_priv*,int,struct rtllib_network*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rtl92e_handle_beacon(struct net_device *dev,
				 struct rtllib_beacon *beacon,
				 struct rtllib_network *network)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	_rtl92e_qos_handle_probe_response(priv, 1, network);

	schedule_delayed_work(&priv->update_beacon_wq, 0);
	return 0;

}