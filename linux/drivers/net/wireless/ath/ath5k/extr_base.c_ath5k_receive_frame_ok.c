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
struct ath5k_rx_status {int rs_status; int rs_phyerr; scalar_t__ rs_keyix; int rs_more; scalar_t__ rs_datalen; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxerr_jumbo; int /*<<< orphan*/  rxerr_mic; int /*<<< orphan*/  rxerr_decrypt; int /*<<< orphan*/ * rxerr_phy_code; int /*<<< orphan*/  rxerr_phy; int /*<<< orphan*/  rxerr_fifo; int /*<<< orphan*/  rxerr_crc; int /*<<< orphan*/  rx_bytes_count; int /*<<< orphan*/  rx_all_count; } ;
struct ath5k_hw {int fif_filter_flags; TYPE_1__ stats; } ;

/* Variables and functions */
 int AR5K_RXERR_CRC ; 
 int AR5K_RXERR_DECRYPT ; 
 int AR5K_RXERR_FIFO ; 
 int AR5K_RXERR_MIC ; 
 int AR5K_RXERR_PHY ; 
 scalar_t__ AR5K_RXKEYIX_INVALID ; 
 size_t AR5K_RX_PHY_ERROR_CCK_RESTART ; 
 size_t AR5K_RX_PHY_ERROR_OFDM_RESTART ; 
 int FIF_FCSFAIL ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
ath5k_receive_frame_ok(struct ath5k_hw *ah, struct ath5k_rx_status *rs)
{
	ah->stats.rx_all_count++;
	ah->stats.rx_bytes_count += rs->rs_datalen;

	if (unlikely(rs->rs_status)) {
		unsigned int filters;

		if (rs->rs_status & AR5K_RXERR_CRC)
			ah->stats.rxerr_crc++;
		if (rs->rs_status & AR5K_RXERR_FIFO)
			ah->stats.rxerr_fifo++;
		if (rs->rs_status & AR5K_RXERR_PHY) {
			ah->stats.rxerr_phy++;
			if (rs->rs_phyerr > 0 && rs->rs_phyerr < 32)
				ah->stats.rxerr_phy_code[rs->rs_phyerr]++;

			/*
			 * Treat packets that underwent a CCK or OFDM reset as having a bad CRC.
			 * These restarts happen when the radio resynchronizes to a stronger frame
			 * while receiving a weaker frame. Here we receive the prefix of the weak
			 * frame. Since these are incomplete packets, mark their CRC as invalid.
			 */
			if (rs->rs_phyerr == AR5K_RX_PHY_ERROR_OFDM_RESTART ||
			    rs->rs_phyerr == AR5K_RX_PHY_ERROR_CCK_RESTART) {
				rs->rs_status |= AR5K_RXERR_CRC;
				rs->rs_status &= ~AR5K_RXERR_PHY;
			} else {
				return false;
			}
		}
		if (rs->rs_status & AR5K_RXERR_DECRYPT) {
			/*
			 * Decrypt error.  If the error occurred
			 * because there was no hardware key, then
			 * let the frame through so the upper layers
			 * can process it.  This is necessary for 5210
			 * parts which have no way to setup a ``clear''
			 * key cache entry.
			 *
			 * XXX do key cache faulting
			 */
			ah->stats.rxerr_decrypt++;
			if (rs->rs_keyix == AR5K_RXKEYIX_INVALID &&
			    !(rs->rs_status & AR5K_RXERR_CRC))
				return true;
		}
		if (rs->rs_status & AR5K_RXERR_MIC) {
			ah->stats.rxerr_mic++;
			return true;
		}

		/*
		 * Reject any frames with non-crypto errors, and take into account the
		 * current FIF_* filters.
		 */
		filters = AR5K_RXERR_DECRYPT;
		if (ah->fif_filter_flags & FIF_FCSFAIL)
			filters |= AR5K_RXERR_CRC;

		if (rs->rs_status & ~filters)
			return false;
	}

	if (unlikely(rs->rs_more)) {
		ah->stats.rxerr_jumbo++;
		return false;
	}
	return true;
}