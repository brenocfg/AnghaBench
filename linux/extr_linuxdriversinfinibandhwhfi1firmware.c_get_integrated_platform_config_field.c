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
typedef  int u32 ;
struct TYPE_2__ {int* cache; } ;
struct hfi1_pportdata {int max_power_class; int default_atten; int port_type; int local_atten; int remote_atten; int rx_preset; int tx_preset_eq; int tx_preset_noeq; TYPE_1__ qsfp_info; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;
typedef  enum platform_config_table_type_encoding { ____Placeholder_platform_config_table_type_encoding } platform_config_table_type_encoding ;

/* Variables and functions */
#define  PLATFORM_CONFIG_PORT_TABLE 133 
#define  PLATFORM_CONFIG_QSFP_ATTEN_TABLE 132 
#define  PLATFORM_CONFIG_RX_PRESET_TABLE 131 
#define  PLATFORM_CONFIG_SYSTEM_TABLE 130 
#define  PLATFORM_CONFIG_TX_PRESET_TABLE 129 
#define  PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE 128 
 int PORT_TABLE_LOCAL_ATTEN_25G ; 
 int PORT_TABLE_PORT_TYPE ; 
 int PORT_TABLE_REMOTE_ATTEN_25G ; 
 size_t QSFP_EQ_INFO_OFFS ; 
 int QSFP_RX_AMP_APPLY_SHIFT ; 
 int QSFP_RX_AMP_APPLY_SMASK ; 
 int QSFP_RX_AMP_SHIFT ; 
 int QSFP_RX_AMP_SMASK ; 
 int QSFP_RX_CDR_APPLY_SHIFT ; 
 int QSFP_RX_CDR_APPLY_SMASK ; 
 int QSFP_RX_CDR_SHIFT ; 
 int QSFP_RX_CDR_SMASK ; 
 int QSFP_RX_EMP_APPLY_SHIFT ; 
 int QSFP_RX_EMP_APPLY_SMASK ; 
 int QSFP_RX_EMP_SHIFT ; 
 int QSFP_RX_EMP_SMASK ; 
 int QSFP_TX_CDR_APPLY_SHIFT ; 
 int QSFP_TX_CDR_APPLY_SMASK ; 
 int QSFP_TX_CDR_SHIFT ; 
 int QSFP_TX_CDR_SMASK ; 
 int QSFP_TX_EQ_APPLY_SHIFT ; 
 int QSFP_TX_EQ_APPLY_SMASK ; 
 int QSFP_TX_EQ_SHIFT ; 
 int QSFP_TX_EQ_SMASK ; 
 int RX_PRESET_TABLE_QSFP_RX_AMP ; 
 int RX_PRESET_TABLE_QSFP_RX_AMP_APPLY ; 
 int RX_PRESET_TABLE_QSFP_RX_CDR ; 
 int RX_PRESET_TABLE_QSFP_RX_CDR_APPLY ; 
 int RX_PRESET_TABLE_QSFP_RX_EMP ; 
 int RX_PRESET_TABLE_QSFP_RX_EMP_APPLY ; 
 int SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_25G ; 
 int SYSTEM_TABLE_QSFP_POWER_CLASS_MAX ; 
 int TX_ATTN_SHIFT ; 
 int TX_ATTN_SMASK ; 
 int TX_POSTCUR_SHIFT ; 
 int TX_POSTCUR_SMASK ; 
 int TX_PRECUR_SHIFT ; 
 int TX_PRECUR_SMASK ; 
 int TX_PRESET_TABLE_ATTN ; 
 int TX_PRESET_TABLE_POSTCUR ; 
 int TX_PRESET_TABLE_PRECUR ; 
 int TX_PRESET_TABLE_QSFP_TX_CDR ; 
 int TX_PRESET_TABLE_QSFP_TX_CDR_APPLY ; 
 int TX_PRESET_TABLE_QSFP_TX_EQ ; 
 int TX_PRESET_TABLE_QSFP_TX_EQ_APPLY ; 

__attribute__((used)) static void get_integrated_platform_config_field(
		struct hfi1_devdata *dd,
		enum platform_config_table_type_encoding table_type,
		int field_index, u32 *data)
{
	struct hfi1_pportdata *ppd = dd->pport;
	u8 *cache = ppd->qsfp_info.cache;
	u32 tx_preset = 0;

	switch (table_type) {
	case PLATFORM_CONFIG_SYSTEM_TABLE:
		if (field_index == SYSTEM_TABLE_QSFP_POWER_CLASS_MAX)
			*data = ppd->max_power_class;
		else if (field_index == SYSTEM_TABLE_QSFP_ATTENUATION_DEFAULT_25G)
			*data = ppd->default_atten;
		break;
	case PLATFORM_CONFIG_PORT_TABLE:
		if (field_index == PORT_TABLE_PORT_TYPE)
			*data = ppd->port_type;
		else if (field_index == PORT_TABLE_LOCAL_ATTEN_25G)
			*data = ppd->local_atten;
		else if (field_index == PORT_TABLE_REMOTE_ATTEN_25G)
			*data = ppd->remote_atten;
		break;
	case PLATFORM_CONFIG_RX_PRESET_TABLE:
		if (field_index == RX_PRESET_TABLE_QSFP_RX_CDR_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_CDR_APPLY_SMASK) >>
				QSFP_RX_CDR_APPLY_SHIFT;
		else if (field_index == RX_PRESET_TABLE_QSFP_RX_EMP_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_EMP_APPLY_SMASK) >>
				QSFP_RX_EMP_APPLY_SHIFT;
		else if (field_index == RX_PRESET_TABLE_QSFP_RX_AMP_APPLY)
			*data = (ppd->rx_preset & QSFP_RX_AMP_APPLY_SMASK) >>
				QSFP_RX_AMP_APPLY_SHIFT;
		else if (field_index == RX_PRESET_TABLE_QSFP_RX_CDR)
			*data = (ppd->rx_preset & QSFP_RX_CDR_SMASK) >>
				QSFP_RX_CDR_SHIFT;
		else if (field_index == RX_PRESET_TABLE_QSFP_RX_EMP)
			*data = (ppd->rx_preset & QSFP_RX_EMP_SMASK) >>
				QSFP_RX_EMP_SHIFT;
		else if (field_index == RX_PRESET_TABLE_QSFP_RX_AMP)
			*data = (ppd->rx_preset & QSFP_RX_AMP_SMASK) >>
				QSFP_RX_AMP_SHIFT;
		break;
	case PLATFORM_CONFIG_TX_PRESET_TABLE:
		if (cache[QSFP_EQ_INFO_OFFS] & 0x4)
			tx_preset = ppd->tx_preset_eq;
		else
			tx_preset = ppd->tx_preset_noeq;
		if (field_index == TX_PRESET_TABLE_PRECUR)
			*data = (tx_preset & TX_PRECUR_SMASK) >>
				TX_PRECUR_SHIFT;
		else if (field_index == TX_PRESET_TABLE_ATTN)
			*data = (tx_preset & TX_ATTN_SMASK) >>
				TX_ATTN_SHIFT;
		else if (field_index == TX_PRESET_TABLE_POSTCUR)
			*data = (tx_preset & TX_POSTCUR_SMASK) >>
				TX_POSTCUR_SHIFT;
		else if (field_index == TX_PRESET_TABLE_QSFP_TX_CDR_APPLY)
			*data = (tx_preset & QSFP_TX_CDR_APPLY_SMASK) >>
				QSFP_TX_CDR_APPLY_SHIFT;
		else if (field_index == TX_PRESET_TABLE_QSFP_TX_EQ_APPLY)
			*data = (tx_preset & QSFP_TX_EQ_APPLY_SMASK) >>
				QSFP_TX_EQ_APPLY_SHIFT;
		else if (field_index == TX_PRESET_TABLE_QSFP_TX_CDR)
			*data = (tx_preset & QSFP_TX_CDR_SMASK) >>
				QSFP_TX_CDR_SHIFT;
		else if (field_index == TX_PRESET_TABLE_QSFP_TX_EQ)
			*data = (tx_preset & QSFP_TX_EQ_SMASK) >>
				QSFP_TX_EQ_SHIFT;
		break;
	case PLATFORM_CONFIG_QSFP_ATTEN_TABLE:
	case PLATFORM_CONFIG_VARIABLE_SETTINGS_TABLE:
	default:
		break;
	}
}