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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN743X_CSR_READ_OP ; 
 int /*<<< orphan*/  MAC_MII_ACC ; 
 int MAC_MII_ACC_MII_BUSY_ ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan743x_mac_mii_wait_till_not_busy(struct lan743x_adapter *adapter)
{
	u32 data;

	return readx_poll_timeout(LAN743X_CSR_READ_OP, MAC_MII_ACC, data,
				  !(data & MAC_MII_ACC_MII_BUSY_), 0, 1000000);
}