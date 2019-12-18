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
typedef  int u8 ;
typedef  int u32 ;
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRH ; 
 int /*<<< orphan*/  ADDRL ; 
 int /*<<< orphan*/  SMSC_ASSERT_MAC_LOCK (struct smsc911x_data*) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
smsc911x_set_hw_mac_address(struct smsc911x_data *pdata, u8 dev_addr[6])
{
	u32 mac_high16 = (dev_addr[5] << 8) | dev_addr[4];
	u32 mac_low32 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
	    (dev_addr[1] << 8) | dev_addr[0];

	SMSC_ASSERT_MAC_LOCK(pdata);

	smsc911x_mac_write(pdata, ADDRH, mac_high16);
	smsc911x_mac_write(pdata, ADDRL, mac_low32);
}