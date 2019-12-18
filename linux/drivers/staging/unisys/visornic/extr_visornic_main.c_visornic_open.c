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

/* Variables and functions */
 int /*<<< orphan*/  VISORNIC_INFINITE_RSP_WAIT ; 
 int /*<<< orphan*/  visornic_enable_with_timeout (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int visornic_open(struct net_device *netdev)
{
	visornic_enable_with_timeout(netdev, VISORNIC_INFINITE_RSP_WAIT);
	return 0;
}