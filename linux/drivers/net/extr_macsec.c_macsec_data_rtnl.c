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
struct net_device {int /*<<< orphan*/  rx_handler_data; } ;
struct macsec_rxh_data {int dummy; } ;

/* Variables and functions */
 struct macsec_rxh_data* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct macsec_rxh_data *macsec_data_rtnl(const struct net_device *dev)
{
	return rtnl_dereference(dev->rx_handler_data);
}