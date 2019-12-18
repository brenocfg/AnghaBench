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
struct net {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct net init_net ; 

__attribute__((used)) static struct net *nsim_devlink_net(struct devlink *devlink)
{
	return &init_net;
}