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
struct expansion_card {int dummy; } ;

/* Variables and functions */
 struct net_device* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ether1_remove(struct expansion_card *ec)
{
	struct net_device *dev = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, NULL);	

	unregister_netdev(dev);
	free_netdev(dev);
	ecard_release_resources(ec);
}