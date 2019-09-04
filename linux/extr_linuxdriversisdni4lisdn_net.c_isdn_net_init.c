#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
struct net_device {scalar_t__ hard_header_len; } ;
struct TYPE_6__ {TYPE_2__** drv; } ;
struct TYPE_5__ {TYPE_1__* interface; } ;
struct TYPE_4__ {scalar_t__ hl_hdrlen; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int ISDN_MAX_DRIVERS ; 
 TYPE_3__* dev ; 

__attribute__((used)) static int
isdn_net_init(struct net_device *ndev)
{
	ushort max_hlhdr_len = 0;
	int drvidx;

	/*
	 *  up till binding we ask the protocol layer to reserve as much
	 *  as we might need for HL layer
	 */

	for (drvidx = 0; drvidx < ISDN_MAX_DRIVERS; drvidx++)
		if (dev->drv[drvidx])
			if (max_hlhdr_len < dev->drv[drvidx]->interface->hl_hdrlen)
				max_hlhdr_len = dev->drv[drvidx]->interface->hl_hdrlen;

	ndev->hard_header_len = ETH_HLEN + max_hlhdr_len;
	return 0;
}