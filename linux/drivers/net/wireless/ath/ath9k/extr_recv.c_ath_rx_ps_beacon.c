#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; } ;
struct TYPE_5__ {scalar_t__ beacon_interval; } ;
struct TYPE_6__ {TYPE_2__ beacon; } ;
struct TYPE_4__ {TYPE_3__ chan; } ;
struct ath_softc {int ps_flags; TYPE_3__* cur_chan; TYPE_1__ offchannel; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 int PS_WAIT_FOR_CAB ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_is_chanctx_enabled () ; 
 int /*<<< orphan*/  ath9k_p2p_beacon_sync (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_set_beacon (struct ath_softc*) ; 
 scalar_t__ ath_beacon_dtim_pending_cab (struct sk_buff*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ath_rx_ps_beacon(struct ath_softc *sc, struct sk_buff *skb)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool skip_beacon = false;

	if (skb->len < 24 + 8 + 2 + 2)
		return;

	sc->ps_flags &= ~PS_WAIT_FOR_BEACON;

	if (sc->ps_flags & PS_BEACON_SYNC) {
		sc->ps_flags &= ~PS_BEACON_SYNC;
		ath_dbg(common, PS,
			"Reconfigure beacon timers based on synchronized timestamp\n");

#ifdef CONFIG_ATH9K_CHANNEL_CONTEXT
		if (ath9k_is_chanctx_enabled()) {
			if (sc->cur_chan == &sc->offchannel.chan)
				skip_beacon = true;
		}
#endif

		if (!skip_beacon &&
		    !(WARN_ON_ONCE(sc->cur_chan->beacon.beacon_interval == 0)))
			ath9k_set_beacon(sc);

		ath9k_p2p_beacon_sync(sc);
	}

	if (ath_beacon_dtim_pending_cab(skb)) {
		/*
		 * Remain awake waiting for buffered broadcast/multicast
		 * frames. If the last broadcast/multicast frame is not
		 * received properly, the next beacon frame will work as
		 * a backup trigger for returning into NETWORK SLEEP state,
		 * so we are waiting for it as well.
		 */
		ath_dbg(common, PS,
			"Received DTIM beacon indicating buffered broadcast/multicast frame(s)\n");
		sc->ps_flags |= PS_WAIT_FOR_CAB | PS_WAIT_FOR_BEACON;
		return;
	}

	if (sc->ps_flags & PS_WAIT_FOR_CAB) {
		/*
		 * This can happen if a broadcast frame is dropped or the AP
		 * fails to send a frame indicating that all CAB frames have
		 * been delivered.
		 */
		sc->ps_flags &= ~PS_WAIT_FOR_CAB;
		ath_dbg(common, PS, "PS wait for CAB frames timed out\n");
	}
}