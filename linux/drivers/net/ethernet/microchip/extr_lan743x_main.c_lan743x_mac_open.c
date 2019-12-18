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
 int /*<<< orphan*/  MAC_RX ; 
 int MAC_RX_RXEN_ ; 
 int /*<<< orphan*/  MAC_TX ; 
 int MAC_TX_TXEN_ ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lan743x_mac_open(struct lan743x_adapter *adapter)
{
	int ret = 0;
	u32 temp;

	temp = lan743x_csr_read(adapter, MAC_RX);
	lan743x_csr_write(adapter, MAC_RX, temp | MAC_RX_RXEN_);
	temp = lan743x_csr_read(adapter, MAC_TX);
	lan743x_csr_write(adapter, MAC_TX, temp | MAC_TX_TXEN_);
	return ret;
}