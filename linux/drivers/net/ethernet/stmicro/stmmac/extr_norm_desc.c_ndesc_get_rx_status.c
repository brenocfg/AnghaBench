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
struct stmmac_extra_stats {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  rx_mii; int /*<<< orphan*/  rx_length; int /*<<< orphan*/  dribbling_bit; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_collision; int /*<<< orphan*/  ipc_csum_error; int /*<<< orphan*/  overflow_error; int /*<<< orphan*/  sa_filter_fail; int /*<<< orphan*/  rx_desc; } ;
struct net_device_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_length_errors; } ;
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 unsigned int RDES0_COLLISION ; 
 unsigned int RDES0_CRC_ERROR ; 
 unsigned int RDES0_DESCRIPTOR_ERROR ; 
 unsigned int RDES0_DRIBBLING ; 
 unsigned int RDES0_ERROR_SUMMARY ; 
 unsigned int RDES0_IPC_CSUM_ERROR ; 
 unsigned int RDES0_LAST_DESCRIPTOR ; 
 unsigned int RDES0_LENGTH_ERROR ; 
 unsigned int RDES0_MII_ERROR ; 
 unsigned int RDES0_OVERFLOW_ERROR ; 
 unsigned int RDES0_OWN ; 
 unsigned int RDES0_SA_FILTER_FAIL ; 
 unsigned int RDES0_VLAN_TAG ; 
 int discard_frame ; 
 int dma_own ; 
 int good_frame ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int ndesc_get_rx_status(void *data, struct stmmac_extra_stats *x,
			       struct dma_desc *p)
{
	int ret = good_frame;
	unsigned int rdes0 = le32_to_cpu(p->des0);
	struct net_device_stats *stats = (struct net_device_stats *)data;

	if (unlikely(rdes0 & RDES0_OWN))
		return dma_own;

	if (unlikely(!(rdes0 & RDES0_LAST_DESCRIPTOR))) {
		stats->rx_length_errors++;
		return discard_frame;
	}

	if (unlikely(rdes0 & RDES0_ERROR_SUMMARY)) {
		if (unlikely(rdes0 & RDES0_DESCRIPTOR_ERROR))
			x->rx_desc++;
		if (unlikely(rdes0 & RDES0_SA_FILTER_FAIL))
			x->sa_filter_fail++;
		if (unlikely(rdes0 & RDES0_OVERFLOW_ERROR))
			x->overflow_error++;
		if (unlikely(rdes0 & RDES0_IPC_CSUM_ERROR))
			x->ipc_csum_error++;
		if (unlikely(rdes0 & RDES0_COLLISION)) {
			x->rx_collision++;
			stats->collisions++;
		}
		if (unlikely(rdes0 & RDES0_CRC_ERROR)) {
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		}
		ret = discard_frame;
	}
	if (unlikely(rdes0 & RDES0_DRIBBLING))
		x->dribbling_bit++;

	if (unlikely(rdes0 & RDES0_LENGTH_ERROR)) {
		x->rx_length++;
		ret = discard_frame;
	}
	if (unlikely(rdes0 & RDES0_MII_ERROR)) {
		x->rx_mii++;
		ret = discard_frame;
	}
#ifdef STMMAC_VLAN_TAG_USED
	if (rdes0 & RDES0_VLAN_TAG)
		x->vlan_tag++;
#endif
	return ret;
}