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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int flags; } ;
struct xcan_priv {TYPE_1__ devtype; } ;

/* Variables and functions */
 int XCAN_FLAG_RX_FIFO_MULTI ; 
 int /*<<< orphan*/  XCAN_IXR_RXNEMP_MASK ; 
 int /*<<< orphan*/  XCAN_IXR_RXOK_MASK ; 

__attribute__((used)) static u32 xcan_rx_int_mask(const struct xcan_priv *priv)
{
	/* RXNEMP is better suited for our use case as it cannot be cleared
	 * while the FIFO is non-empty, but CAN FD HW does not have it
	 */
	if (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI)
		return XCAN_IXR_RXOK_MASK;
	else
		return XCAN_IXR_RXNEMP_MASK;
}