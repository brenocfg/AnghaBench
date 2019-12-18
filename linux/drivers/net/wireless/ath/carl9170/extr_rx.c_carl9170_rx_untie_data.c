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
typedef  int u8 ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ar9170_rx_phystatus {int dummy; } ;
struct ar9170_rx_macstatus {int status; } ;
struct ar9170_rx_head {int dummy; } ;
struct ar9170 {int rx_has_plcp; int /*<<< orphan*/  rx_dropped; struct ar9170_rx_head rx_plcp; TYPE_1__* hw; int /*<<< orphan*/  ampdu_ref; } ;
typedef  int /*<<< orphan*/  status ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int AR9170_RX_STATUS_MPDU ; 
#define  AR9170_RX_STATUS_MPDU_FIRST 131 
#define  AR9170_RX_STATUS_MPDU_LAST 130 
#define  AR9170_RX_STATUS_MPDU_MIDDLE 129 
#define  AR9170_RX_STATUS_MPDU_SINGLE 128 
 int /*<<< orphan*/  BUG () ; 
 int ETH_ALEN ; 
 int FCS_LEN ; 
 int /*<<< orphan*/  IS_STARTED (struct ar9170*) ; 
 int /*<<< orphan*/  RX_FLAG_AMPDU_IS_LAST ; 
 int /*<<< orphan*/  RX_FLAG_NO_SIGNAL_VAL ; 
 int /*<<< orphan*/  carl9170_ampdu_check (struct ar9170*,int*,int,struct ieee80211_rx_status*) ; 
 scalar_t__ carl9170_handle_mpdu (struct ar9170*,int*,int,struct ieee80211_rx_status*) ; 
 int carl9170_rx_mac_status (struct ar9170*,struct ar9170_rx_head*,struct ar9170_rx_macstatus*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  carl9170_rx_phy_status (struct ar9170*,struct ar9170_rx_phystatus*,struct ieee80211_rx_status*) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  memcpy (struct ar9170_rx_head*,void*,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_ratelimit () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void carl9170_rx_untie_data(struct ar9170 *ar, u8 *buf, int len)
{
	struct ar9170_rx_head *head;
	struct ar9170_rx_macstatus *mac;
	struct ar9170_rx_phystatus *phy = NULL;
	struct ieee80211_rx_status status;
	int mpdu_len;
	u8 mac_status;

	if (!IS_STARTED(ar))
		return;

	if (unlikely(len < sizeof(*mac)))
		goto drop;

	memset(&status, 0, sizeof(status));

	mpdu_len = len - sizeof(*mac);

	mac = (void *)(buf + mpdu_len);
	mac_status = mac->status;
	switch (mac_status & AR9170_RX_STATUS_MPDU) {
	case AR9170_RX_STATUS_MPDU_FIRST:
		ar->ampdu_ref++;
		/* Aggregated MPDUs start with an PLCP header */
		if (likely(mpdu_len >= sizeof(struct ar9170_rx_head))) {
			head = (void *) buf;

			/*
			 * The PLCP header needs to be cached for the
			 * following MIDDLE + LAST A-MPDU packets.
			 *
			 * So, if you are wondering why all frames seem
			 * to share a common RX status information,
			 * then you have the answer right here...
			 */
			memcpy(&ar->rx_plcp, (void *) buf,
			       sizeof(struct ar9170_rx_head));

			mpdu_len -= sizeof(struct ar9170_rx_head);
			buf += sizeof(struct ar9170_rx_head);

			ar->rx_has_plcp = true;
		} else {
			if (net_ratelimit()) {
				wiphy_err(ar->hw->wiphy, "plcp info "
					"is clipped.\n");
			}

			goto drop;
		}
		break;

	case AR9170_RX_STATUS_MPDU_LAST:
		status.flag |= RX_FLAG_AMPDU_IS_LAST;

		/*
		 * The last frame of an A-MPDU has an extra tail
		 * which does contain the phy status of the whole
		 * aggregate.
		 */
		if (likely(mpdu_len >= sizeof(struct ar9170_rx_phystatus))) {
			mpdu_len -= sizeof(struct ar9170_rx_phystatus);
			phy = (void *)(buf + mpdu_len);
		} else {
			if (net_ratelimit()) {
				wiphy_err(ar->hw->wiphy, "frame tail "
					"is clipped.\n");
			}

			goto drop;
		}
		/* fall through */

	case AR9170_RX_STATUS_MPDU_MIDDLE:
		/*  These are just data + mac status */
		if (unlikely(!ar->rx_has_plcp)) {
			if (!net_ratelimit())
				return;

			wiphy_err(ar->hw->wiphy, "rx stream does not start "
					"with a first_mpdu frame tag.\n");

			goto drop;
		}

		head = &ar->rx_plcp;
		break;

	case AR9170_RX_STATUS_MPDU_SINGLE:
		/* single mpdu has both: plcp (head) and phy status (tail) */
		head = (void *) buf;

		mpdu_len -= sizeof(struct ar9170_rx_head);
		mpdu_len -= sizeof(struct ar9170_rx_phystatus);

		buf += sizeof(struct ar9170_rx_head);
		phy = (void *)(buf + mpdu_len);
		break;

	default:
		BUG();
		break;
	}

	/* FC + DU + RA + FCS */
	if (unlikely(mpdu_len < (2 + 2 + ETH_ALEN + FCS_LEN)))
		goto drop;

	if (unlikely(carl9170_rx_mac_status(ar, head, mac, &status)))
		goto drop;

	if (!carl9170_ampdu_check(ar, buf, mac_status, &status))
		goto drop;

	if (phy)
		carl9170_rx_phy_status(ar, phy, &status);
	else
		status.flag |= RX_FLAG_NO_SIGNAL_VAL;

	if (carl9170_handle_mpdu(ar, buf, mpdu_len, &status))
		goto drop;

	return;
drop:
	ar->rx_dropped++;
}