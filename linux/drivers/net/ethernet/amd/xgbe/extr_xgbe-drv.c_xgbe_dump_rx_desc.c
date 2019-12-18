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
struct xgbe_ring_desc {int /*<<< orphan*/  desc3; int /*<<< orphan*/  desc2; int /*<<< orphan*/  desc1; int /*<<< orphan*/  desc0; } ;
struct xgbe_ring_data {struct xgbe_ring_desc* rdesc; } ;
struct xgbe_ring {int dummy; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xgbe_dump_rx_desc(struct xgbe_prv_data *pdata, struct xgbe_ring *ring,
		       unsigned int idx)
{
	struct xgbe_ring_data *rdata;
	struct xgbe_ring_desc *rdesc;

	rdata = XGBE_GET_DESC_DATA(ring, idx);
	rdesc = rdata->rdesc;
	netdev_dbg(pdata->netdev,
		   "RX_NORMAL_DESC[%d RX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx, le32_to_cpu(rdesc->desc0), le32_to_cpu(rdesc->desc1),
		   le32_to_cpu(rdesc->desc2), le32_to_cpu(rdesc->desc3));
}