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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int sh_eth_read (struct net_device*,int) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int) ; 

__attribute__((used)) static void sh_eth_modify(struct net_device *ndev, int enum_index, u32 clear,
			  u32 set)
{
	sh_eth_write(ndev, (sh_eth_read(ndev, enum_index) & ~clear) | set,
		     enum_index);
}