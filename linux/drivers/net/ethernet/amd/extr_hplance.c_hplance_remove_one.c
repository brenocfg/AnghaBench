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
struct dio_dev {int dummy; } ;

/* Variables and functions */
 struct net_device* dio_get_drvdata (struct dio_dev*) ; 
 int /*<<< orphan*/  dio_resource_len (struct dio_dev*) ; 
 int /*<<< orphan*/  dio_resource_start (struct dio_dev*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void hplance_remove_one(struct dio_dev *d)
{
	struct net_device *dev = dio_get_drvdata(d);

	unregister_netdev(dev);
	release_mem_region(dio_resource_start(d), dio_resource_len(d));
	free_netdev(dev);
}