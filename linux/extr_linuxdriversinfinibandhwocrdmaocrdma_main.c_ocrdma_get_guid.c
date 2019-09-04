#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * mac_addr; } ;
struct ocrdma_dev {TYPE_1__ nic_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ocrdma_get_guid(struct ocrdma_dev *dev, u8 *guid)
{
	u8 mac_addr[6];

	memcpy(&mac_addr[0], &dev->nic_info.mac_addr[0], ETH_ALEN);
	guid[0] = mac_addr[0] ^ 2;
	guid[1] = mac_addr[1];
	guid[2] = mac_addr[2];
	guid[3] = 0xff;
	guid[4] = 0xfe;
	guid[5] = mac_addr[3];
	guid[6] = mac_addr[4];
	guid[7] = mac_addr[5];
}