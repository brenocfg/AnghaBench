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
struct vector_private {int /*<<< orphan*/ * fds; } ;
struct vector_device {int /*<<< orphan*/  pdev; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct vector_device* find_device (int) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int vector_remove(int n, char **error_out)
{
	struct vector_device *vec_d;
	struct net_device *dev;
	struct vector_private *vp;

	vec_d = find_device(n);
	if (vec_d == NULL)
		return -ENODEV;
	dev = vec_d->dev;
	vp = netdev_priv(dev);
	if (vp->fds != NULL)
		return -EBUSY;
	unregister_netdev(dev);
	platform_device_unregister(&vec_d->pdev);
	return 0;
}