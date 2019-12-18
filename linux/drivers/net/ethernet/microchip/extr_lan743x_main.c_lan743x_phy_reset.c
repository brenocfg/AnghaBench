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
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_ETH_PHY_RST_ ; 
 int PMT_CTL_READY_ ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int lan743x_phy_reset(struct lan743x_adapter *adapter)
{
	u32 data;

	/* Only called with in probe, and before mdiobus_register */

	data = lan743x_csr_read(adapter, PMT_CTL);
	data |= PMT_CTL_ETH_PHY_RST_;
	lan743x_csr_write(adapter, PMT_CTL, data);

	return readx_poll_timeout(LAN743X_CSR_READ_OP, PMT_CTL, data,
				  (!(data & PMT_CTL_ETH_PHY_RST_) &&
				  (data & PMT_CTL_READY_)),
				  50000, 1000000);
}