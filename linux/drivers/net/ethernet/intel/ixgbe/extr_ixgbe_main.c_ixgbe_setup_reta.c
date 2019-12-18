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
typedef  int u32 ;
typedef  int u16 ;
struct ixgbe_adapter {int flags; int* rss_indir_tbl; TYPE_1__* ring_feature; } ;
struct TYPE_2__ {int indices; } ;

/* Variables and functions */
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 size_t RING_F_RSS ; 
 int ixgbe_rss_indir_tbl_entries (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_store_key (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_store_reta (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ixgbe_setup_reta(struct ixgbe_adapter *adapter)
{
	u32 i, j;
	u32 reta_entries = ixgbe_rss_indir_tbl_entries(adapter);
	u16 rss_i = adapter->ring_feature[RING_F_RSS].indices;

	/* Program table for at least 4 queues w/ SR-IOV so that VFs can
	 * make full use of any rings they may have.  We will use the
	 * PSRTYPE register to control how many rings we use within the PF.
	 */
	if ((adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) && (rss_i < 4))
		rss_i = 4;

	/* Fill out hash function seeds */
	ixgbe_store_key(adapter);

	/* Fill out redirection table */
	memset(adapter->rss_indir_tbl, 0, sizeof(adapter->rss_indir_tbl));

	for (i = 0, j = 0; i < reta_entries; i++, j++) {
		if (j == rss_i)
			j = 0;

		adapter->rss_indir_tbl[i] = j;
	}

	ixgbe_store_reta(adapter);
}