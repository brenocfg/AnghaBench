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
typedef  int /*<<< orphan*/  u32 ;
struct rndis_device {int /*<<< orphan*/  hw_mac_adr; } ;
struct netvsc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  RNDIS_OID_802_3_PERMANENT_ADDRESS ; 
 int rndis_filter_query_device (struct rndis_device*,struct netvsc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rndis_filter_query_device_mac(struct rndis_device *dev,
					 struct netvsc_device *net_device)
{
	u32 size = ETH_ALEN;

	return rndis_filter_query_device(dev, net_device,
				      RNDIS_OID_802_3_PERMANENT_ADDRESS,
				      dev->hw_mac_adr, &size);
}