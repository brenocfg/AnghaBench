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
struct pcnet_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct ei_device {int dummy; } ;

/* Variables and functions */
 char* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct pcnet_dev *PRIV(struct net_device *dev)
{
	char *p = netdev_priv(dev);
	return (struct pcnet_dev *)(p + sizeof(struct ei_device));
}