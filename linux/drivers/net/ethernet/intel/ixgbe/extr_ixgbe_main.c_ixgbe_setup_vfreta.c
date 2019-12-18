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
typedef  int u16 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int num_rx_pools; int* rss_indir_tbl; int /*<<< orphan*/ * rss_key; TYPE_1__* ring_feature; struct ixgbe_hw hw; } ;
struct TYPE_2__ {int indices; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_PFVFRSSRK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  VMDQ_P (int) ; 
 int /*<<< orphan*/  ixgbe_store_vfreta (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_setup_vfreta(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;
	int i, j;

	/* Fill out hash function seeds */
	for (i = 0; i < 10; i++) {
		u16 pool = adapter->num_rx_pools;

		while (pool--)
			IXGBE_WRITE_REG(hw,
					IXGBE_PFVFRSSRK(i, VMDQ_P(pool)),
					*(adapter->rss_key + i));
	}

	/* Fill out the redirection table */
	for (i = 0, j = 0; i < 64; i++, j++) {
		if (j == rss_i)
			j = 0;

		adapter->rss_indir_tbl[i] = j;
	}

	ixgbe_store_vfreta(adapter);
}