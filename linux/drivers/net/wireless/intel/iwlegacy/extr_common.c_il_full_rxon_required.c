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
struct il_rxon_cmd {int dev_type; int channel; int air_propagation; int ofdm_ht_single_stream_basic_rates; int ofdm_ht_dual_stream_basic_rates; int assoc_id; int flags; int filter_flags; int /*<<< orphan*/  wlap_bssid_addr; int /*<<< orphan*/  node_addr; int /*<<< orphan*/  bssid_addr; } ;
struct il_priv {struct il_rxon_cmd active; struct il_rxon_cmd staging; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK (int) ; 
 int /*<<< orphan*/  CHK_NEQ (int,int) ; 
 int RXON_FILTER_ASSOC_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int /*<<< orphan*/  ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_is_associated (struct il_priv*) ; 

int
il_full_rxon_required(struct il_priv *il)
{
	const struct il_rxon_cmd *staging = &il->staging;
	const struct il_rxon_cmd *active = &il->active;

#define CHK(cond)							\
	if ((cond)) {							\
		D_INFO("need full RXON - " #cond "\n");	\
		return 1;						\
	}

#define CHK_NEQ(c1, c2)						\
	if ((c1) != (c2)) {					\
		D_INFO("need full RXON - "	\
			       #c1 " != " #c2 " - %d != %d\n",	\
			       (c1), (c2));			\
		return 1;					\
	}

	/* These items are only settable from the full RXON command */
	CHK(!il_is_associated(il));
	CHK(!ether_addr_equal_64bits(staging->bssid_addr, active->bssid_addr));
	CHK(!ether_addr_equal_64bits(staging->node_addr, active->node_addr));
	CHK(!ether_addr_equal_64bits(staging->wlap_bssid_addr,
				     active->wlap_bssid_addr));
	CHK_NEQ(staging->dev_type, active->dev_type);
	CHK_NEQ(staging->channel, active->channel);
	CHK_NEQ(staging->air_propagation, active->air_propagation);
	CHK_NEQ(staging->ofdm_ht_single_stream_basic_rates,
		active->ofdm_ht_single_stream_basic_rates);
	CHK_NEQ(staging->ofdm_ht_dual_stream_basic_rates,
		active->ofdm_ht_dual_stream_basic_rates);
	CHK_NEQ(staging->assoc_id, active->assoc_id);

	/* flags, filter_flags, ofdm_basic_rates, and cck_basic_rates can
	 * be updated with the RXON_ASSOC command -- however only some
	 * flag transitions are allowed using RXON_ASSOC */

	/* Check if we are not switching bands */
	CHK_NEQ(staging->flags & RXON_FLG_BAND_24G_MSK,
		active->flags & RXON_FLG_BAND_24G_MSK);

	/* Check if we are switching association toggle */
	CHK_NEQ(staging->filter_flags & RXON_FILTER_ASSOC_MSK,
		active->filter_flags & RXON_FILTER_ASSOC_MSK);

#undef CHK
#undef CHK_NEQ

	return 0;
}