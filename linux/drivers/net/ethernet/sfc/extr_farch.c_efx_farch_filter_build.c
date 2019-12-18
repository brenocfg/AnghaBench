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
struct efx_farch_filter_spec {int flags; int dmaq_id; int* data; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EFX_DWORD_0 ; 
 int /*<<< orphan*/  EFX_DWORD_1 ; 
 int /*<<< orphan*/  EFX_DWORD_2 ; 
 int /*<<< orphan*/  EFX_FARCH_FILTER_MAC_WILD ; 
#define  EFX_FARCH_FILTER_TABLE_RX_IP 130 
#define  EFX_FARCH_FILTER_TABLE_RX_MAC 129 
#define  EFX_FARCH_FILTER_TABLE_TX_MAC 128 
 int /*<<< orphan*/  EFX_FARCH_FILTER_UDP_FULL ; 
 int /*<<< orphan*/  EFX_FARCH_FILTER_UDP_WILD ; 
 int EFX_FILTER_FLAG_RX_RSS ; 
 int EFX_FILTER_FLAG_RX_SCATTER ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_BZ_RSS_EN ; 
 int /*<<< orphan*/  FRF_BZ_RXQ_ID ; 
 int /*<<< orphan*/  FRF_BZ_SCATTER_EN ; 
 int /*<<< orphan*/  FRF_BZ_TCP_UDP ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_DEST_MAC_HI ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_DEST_MAC_LO ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_RSS_EN ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_RXQ_ID ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_SCATTER_EN ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_VLAN_ID ; 
 int /*<<< orphan*/  FRF_CZ_RMFT_WILDCARD_MATCH ; 
 int /*<<< orphan*/  FRF_CZ_TMFT_SRC_MAC_HI ; 
 int /*<<< orphan*/  FRF_CZ_TMFT_SRC_MAC_LO ; 
 int /*<<< orphan*/  FRF_CZ_TMFT_TXQ_ID ; 
 int /*<<< orphan*/  FRF_CZ_TMFT_VLAN_ID ; 
 int /*<<< orphan*/  FRF_CZ_TMFT_WILDCARD_MATCH ; 
 int efx_farch_filter_spec_table_id (struct efx_farch_filter_spec*) ; 

__attribute__((used)) static u32 efx_farch_filter_build(efx_oword_t *filter,
				  struct efx_farch_filter_spec *spec)
{
	u32 data3;

	switch (efx_farch_filter_spec_table_id(spec)) {
	case EFX_FARCH_FILTER_TABLE_RX_IP: {
		bool is_udp = (spec->type == EFX_FARCH_FILTER_UDP_FULL ||
			       spec->type == EFX_FARCH_FILTER_UDP_WILD);
		EFX_POPULATE_OWORD_7(
			*filter,
			FRF_BZ_RSS_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_RSS),
			FRF_BZ_SCATTER_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_SCATTER),
			FRF_BZ_TCP_UDP, is_udp,
			FRF_BZ_RXQ_ID, spec->dmaq_id,
			EFX_DWORD_2, spec->data[2],
			EFX_DWORD_1, spec->data[1],
			EFX_DWORD_0, spec->data[0]);
		data3 = is_udp;
		break;
	}

	case EFX_FARCH_FILTER_TABLE_RX_MAC: {
		bool is_wild = spec->type == EFX_FARCH_FILTER_MAC_WILD;
		EFX_POPULATE_OWORD_7(
			*filter,
			FRF_CZ_RMFT_RSS_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_RSS),
			FRF_CZ_RMFT_SCATTER_EN,
			!!(spec->flags & EFX_FILTER_FLAG_RX_SCATTER),
			FRF_CZ_RMFT_RXQ_ID, spec->dmaq_id,
			FRF_CZ_RMFT_WILDCARD_MATCH, is_wild,
			FRF_CZ_RMFT_DEST_MAC_HI, spec->data[2],
			FRF_CZ_RMFT_DEST_MAC_LO, spec->data[1],
			FRF_CZ_RMFT_VLAN_ID, spec->data[0]);
		data3 = is_wild;
		break;
	}

	case EFX_FARCH_FILTER_TABLE_TX_MAC: {
		bool is_wild = spec->type == EFX_FARCH_FILTER_MAC_WILD;
		EFX_POPULATE_OWORD_5(*filter,
				     FRF_CZ_TMFT_TXQ_ID, spec->dmaq_id,
				     FRF_CZ_TMFT_WILDCARD_MATCH, is_wild,
				     FRF_CZ_TMFT_SRC_MAC_HI, spec->data[2],
				     FRF_CZ_TMFT_SRC_MAC_LO, spec->data[1],
				     FRF_CZ_TMFT_VLAN_ID, spec->data[0]);
		data3 = is_wild | spec->dmaq_id << 1;
		break;
	}

	default:
		BUG();
	}

	return spec->data[0] ^ spec->data[1] ^ spec->data[2] ^ data3;
}