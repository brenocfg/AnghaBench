#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_3__ {int* tx_modq; int vlan_pri_map; int ingress_config; int rx_pkt_encap; int vnic_shift; int hash_filter_mask; void* frag_shift; void* matchtype_shift; void* macmatch_shift; void* ethertype_shift; void* protocol_shift; void* tos_shift; void* vlan_shift; void* port_shift; void* fcoe_shift; int /*<<< orphan*/  dack_re; int /*<<< orphan*/  tre; } ;
struct TYPE_4__ {TYPE_1__ tp; int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CHELSIO_T5 ; 
 int CRXPKTENC_F ; 
 int /*<<< orphan*/  DELAYEDACKRESOLUTION_G (int) ; 
 int /*<<< orphan*/  ETHERTYPE_F ; 
 int /*<<< orphan*/  FCOE_F ; 
 int /*<<< orphan*/  FRAGMENTATION_F ; 
 int /*<<< orphan*/  LE_3_DB_HASH_MASK_GEN_IPV4_T6_A ; 
 int /*<<< orphan*/  LE_4_DB_HASH_MASK_GEN_IPV4_T6_A ; 
 int /*<<< orphan*/  MACMATCH_F ; 
 int /*<<< orphan*/  MPSHITTYPE_F ; 
 int NCHAN ; 
 int /*<<< orphan*/  PORT_F ; 
 int /*<<< orphan*/  PROTOCOL_F ; 
 int /*<<< orphan*/  TIMERRESOLUTION_G (int) ; 
 int /*<<< orphan*/  TOS_F ; 
 int /*<<< orphan*/  TP_INGRESS_CONFIG_A ; 
 int /*<<< orphan*/  TP_OUT_CONFIG_A ; 
 int /*<<< orphan*/  TP_TIMER_RESOLUTION_A ; 
 int /*<<< orphan*/  TP_VLAN_PRI_MAP_A ; 
 int /*<<< orphan*/  VLAN_F ; 
 int VNIC_F ; 
 int /*<<< orphan*/  VNIC_ID_F ; 
 void* t4_filter_field_shift (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_tp_pio_read (struct adapter*,int*,int,int /*<<< orphan*/ ,int) ; 

int t4_init_tp_params(struct adapter *adap, bool sleep_ok)
{
	int chan;
	u32 v;

	v = t4_read_reg(adap, TP_TIMER_RESOLUTION_A);
	adap->params.tp.tre = TIMERRESOLUTION_G(v);
	adap->params.tp.dack_re = DELAYEDACKRESOLUTION_G(v);

	/* MODQ_REQ_MAP defaults to setting queues 0-3 to chan 0-3 */
	for (chan = 0; chan < NCHAN; chan++)
		adap->params.tp.tx_modq[chan] = chan;

	/* Cache the adapter's Compressed Filter Mode and global Incress
	 * Configuration.
	 */
	t4_tp_pio_read(adap, &adap->params.tp.vlan_pri_map, 1,
		       TP_VLAN_PRI_MAP_A, sleep_ok);
	t4_tp_pio_read(adap, &adap->params.tp.ingress_config, 1,
		       TP_INGRESS_CONFIG_A, sleep_ok);

	/* For T6, cache the adapter's compressed error vector
	 * and passing outer header info for encapsulated packets.
	 */
	if (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) {
		v = t4_read_reg(adap, TP_OUT_CONFIG_A);
		adap->params.tp.rx_pkt_encap = (v & CRXPKTENC_F) ? 1 : 0;
	}

	/* Now that we have TP_VLAN_PRI_MAP cached, we can calculate the field
	 * shift positions of several elements of the Compressed Filter Tuple
	 * for this adapter which we need frequently ...
	 */
	adap->params.tp.fcoe_shift = t4_filter_field_shift(adap, FCOE_F);
	adap->params.tp.port_shift = t4_filter_field_shift(adap, PORT_F);
	adap->params.tp.vnic_shift = t4_filter_field_shift(adap, VNIC_ID_F);
	adap->params.tp.vlan_shift = t4_filter_field_shift(adap, VLAN_F);
	adap->params.tp.tos_shift = t4_filter_field_shift(adap, TOS_F);
	adap->params.tp.protocol_shift = t4_filter_field_shift(adap,
							       PROTOCOL_F);
	adap->params.tp.ethertype_shift = t4_filter_field_shift(adap,
								ETHERTYPE_F);
	adap->params.tp.macmatch_shift = t4_filter_field_shift(adap,
							       MACMATCH_F);
	adap->params.tp.matchtype_shift = t4_filter_field_shift(adap,
								MPSHITTYPE_F);
	adap->params.tp.frag_shift = t4_filter_field_shift(adap,
							   FRAGMENTATION_F);

	/* If TP_INGRESS_CONFIG.VNID == 0, then TP_VLAN_PRI_MAP.VNIC_ID
	 * represents the presence of an Outer VLAN instead of a VNIC ID.
	 */
	if ((adap->params.tp.ingress_config & VNIC_F) == 0)
		adap->params.tp.vnic_shift = -1;

	v = t4_read_reg(adap, LE_3_DB_HASH_MASK_GEN_IPV4_T6_A);
	adap->params.tp.hash_filter_mask = v;
	v = t4_read_reg(adap, LE_4_DB_HASH_MASK_GEN_IPV4_T6_A);
	adap->params.tp.hash_filter_mask |= ((u64)v << 32);
	return 0;
}