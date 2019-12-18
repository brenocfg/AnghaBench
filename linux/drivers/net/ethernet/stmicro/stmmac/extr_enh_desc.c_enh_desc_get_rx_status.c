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
struct stmmac_extra_stats {int /*<<< orphan*/  rx_vlan; int /*<<< orphan*/  rx_length; int /*<<< orphan*/  da_rx_filter_fail; int /*<<< orphan*/  sa_rx_filter_fail; int /*<<< orphan*/  dribbling_bit; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_mii; int /*<<< orphan*/  rx_watchdog; int /*<<< orphan*/  rx_gmac_overflow; int /*<<< orphan*/  rx_desc; } ;
struct net_device_stats {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  rx_length_errors; } ;
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 unsigned int ERDES0_RX_MAC_ADDR ; 
 unsigned int RDES0_COLLISION ; 
 unsigned int RDES0_CRC_ERROR ; 
 unsigned int RDES0_DA_FILTER_FAIL ; 
 unsigned int RDES0_DESCRIPTOR_ERROR ; 
 unsigned int RDES0_DRIBBLING ; 
 unsigned int RDES0_ERROR_SUMMARY ; 
 unsigned int RDES0_FRAME_TYPE ; 
 unsigned int RDES0_IPC_CSUM_ERROR ; 
 unsigned int RDES0_LAST_DESCRIPTOR ; 
 unsigned int RDES0_LENGTH_ERROR ; 
 unsigned int RDES0_MII_ERROR ; 
 unsigned int RDES0_OVERFLOW_ERROR ; 
 unsigned int RDES0_OWN ; 
 unsigned int RDES0_RECEIVE_WATCHDOG ; 
 unsigned int RDES0_SA_FILTER_FAIL ; 
 unsigned int RDES0_VLAN_TAG ; 
 int discard_frame ; 
 int dma_own ; 
 int enh_desc_coe_rdes0 (int,int,int) ; 
 int good_frame ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int enh_desc_get_rx_status(void *data, struct stmmac_extra_stats *x,
				  struct dma_desc *p)
{
	struct net_device_stats *stats = (struct net_device_stats *)data;
	unsigned int rdes0 = le32_to_cpu(p->des0);
	int ret = good_frame;

	if (unlikely(rdes0 & RDES0_OWN))
		return dma_own;

	if (unlikely(!(rdes0 & RDES0_LAST_DESCRIPTOR))) {
		stats->rx_length_errors++;
		return discard_frame;
	}

	if (unlikely(rdes0 & RDES0_ERROR_SUMMARY)) {
		if (unlikely(rdes0 & RDES0_DESCRIPTOR_ERROR)) {
			x->rx_desc++;
			stats->rx_length_errors++;
		}
		if (unlikely(rdes0 & RDES0_OVERFLOW_ERROR))
			x->rx_gmac_overflow++;

		if (unlikely(rdes0 & RDES0_IPC_CSUM_ERROR))
			pr_err("\tIPC Csum Error/Giant frame\n");

		if (unlikely(rdes0 & RDES0_COLLISION))
			stats->collisions++;
		if (unlikely(rdes0 & RDES0_RECEIVE_WATCHDOG))
			x->rx_watchdog++;

		if (unlikely(rdes0 & RDES0_MII_ERROR))	/* GMII */
			x->rx_mii++;

		if (unlikely(rdes0 & RDES0_CRC_ERROR)) {
			x->rx_crc_errors++;
			stats->rx_crc_errors++;
		}
		ret = discard_frame;
	}

	/* After a payload csum error, the ES bit is set.
	 * It doesn't match with the information reported into the databook.
	 * At any rate, we need to understand if the CSUM hw computation is ok
	 * and report this info to the upper layers. */
	if (likely(ret == good_frame))
		ret = enh_desc_coe_rdes0(!!(rdes0 & RDES0_IPC_CSUM_ERROR),
					 !!(rdes0 & RDES0_FRAME_TYPE),
					 !!(rdes0 & ERDES0_RX_MAC_ADDR));

	if (unlikely(rdes0 & RDES0_DRIBBLING))
		x->dribbling_bit++;

	if (unlikely(rdes0 & RDES0_SA_FILTER_FAIL)) {
		x->sa_rx_filter_fail++;
		ret = discard_frame;
	}
	if (unlikely(rdes0 & RDES0_DA_FILTER_FAIL)) {
		x->da_rx_filter_fail++;
		ret = discard_frame;
	}
	if (unlikely(rdes0 & RDES0_LENGTH_ERROR)) {
		x->rx_length++;
		ret = discard_frame;
	}
#ifdef STMMAC_VLAN_TAG_USED
	if (rdes0 & RDES0_VLAN_TAG)
		x->rx_vlan++;
#endif

	return ret;
}