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
struct net_device {int dummy; } ;
struct lio {int /*<<< orphan*/  oct_dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int OCT_PRIV_FLAG_TX_BYTES ; 
 int /*<<< orphan*/  lio_set_priv_flag (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lio_set_priv_flags(struct net_device *netdev, u32 flags)
{
	struct lio *lio = GET_LIO(netdev);
	bool intr_by_tx_bytes = !!(flags & (0x1 << OCT_PRIV_FLAG_TX_BYTES));

	lio_set_priv_flag(lio->oct_dev, OCT_PRIV_FLAG_TX_BYTES,
			  intr_by_tx_bytes);
	return 0;
}