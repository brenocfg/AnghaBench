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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct sff_trasnceiver_codes_byte5 {scalar_t__ fc_sw_laser_sn; scalar_t__ fc_sw_laser_sl; } ;
struct sff_trasnceiver_codes_byte4 {scalar_t__ fc_lw_laser; scalar_t__ fc_sw_laser; } ;
struct TYPE_2__ {void* flags; void* vcc; void* tx_power; void* tx_bias; void* rx_power; void* temperature; } ;
struct fc_rdp_sfp_desc {void* length; TYPE_1__ sfp_info; void* tag; } ;

/* Variables and functions */
 int RDP_SFP_DESC_TAG ; 
 int SFF_PG0_CONNECTOR_LC ; 
 int SFF_PG0_IDENT_SFP ; 
 size_t SFF_RXPOWER_B0 ; 
 size_t SFF_RXPOWER_B1 ; 
 size_t SFF_TEMPERATURE_B0 ; 
 size_t SFF_TEMPERATURE_B1 ; 
 size_t SFF_TXPOWER_B0 ; 
 size_t SFF_TXPOWER_B1 ; 
 size_t SFF_TX_BIAS_CURRENT_B0 ; 
 size_t SFF_TX_BIAS_CURRENT_B1 ; 
 size_t SFF_VCC_B0 ; 
 size_t SFF_VCC_B1 ; 
 int SFP_FLAG_CT_SFP_PLUS ; 
 int SFP_FLAG_CT_SHIFT ; 
 int SFP_FLAG_CT_UNKNOWN ; 
 int SFP_FLAG_IS_OPTICAL_PORT ; 
 int SFP_FLAG_IS_OPTICAL_SHIFT ; 
 int SFP_FLAG_PT_LWLASER_LC1310 ; 
 int SFP_FLAG_PT_LWLASER_LL1550 ; 
 int SFP_FLAG_PT_SHIFT ; 
 int SFP_FLAG_PT_SWLASER ; 
 int SFP_WAVELENGTH_LC1310 ; 
 int SFP_WAVELENGTH_LL1550 ; 
 size_t SSF_CONNECTOR ; 
 size_t SSF_IDENTIFIER ; 
 size_t SSF_TRANSCEIVER_CODE_B4 ; 
 size_t SSF_TRANSCEIVER_CODE_B5 ; 
 size_t SSF_WAVELENGTH_B0 ; 
 size_t SSF_WAVELENGTH_B1 ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_sfp_desc(struct fc_rdp_sfp_desc *desc,
		uint8_t *page_a0, uint8_t *page_a2)
{
	uint16_t wavelength;
	uint16_t temperature;
	uint16_t rx_power;
	uint16_t tx_bias;
	uint16_t tx_power;
	uint16_t vcc;
	uint16_t flag = 0;
	struct sff_trasnceiver_codes_byte4 *trasn_code_byte4;
	struct sff_trasnceiver_codes_byte5 *trasn_code_byte5;

	desc->tag = cpu_to_be32(RDP_SFP_DESC_TAG);

	trasn_code_byte4 = (struct sff_trasnceiver_codes_byte4 *)
			&page_a0[SSF_TRANSCEIVER_CODE_B4];
	trasn_code_byte5 = (struct sff_trasnceiver_codes_byte5 *)
			&page_a0[SSF_TRANSCEIVER_CODE_B5];

	if ((trasn_code_byte4->fc_sw_laser) ||
	    (trasn_code_byte5->fc_sw_laser_sl) ||
	    (trasn_code_byte5->fc_sw_laser_sn)) {  /* check if its short WL */
		flag |= (SFP_FLAG_PT_SWLASER << SFP_FLAG_PT_SHIFT);
	} else if (trasn_code_byte4->fc_lw_laser) {
		wavelength = (page_a0[SSF_WAVELENGTH_B1] << 8) |
			page_a0[SSF_WAVELENGTH_B0];
		if (wavelength == SFP_WAVELENGTH_LC1310)
			flag |= SFP_FLAG_PT_LWLASER_LC1310 << SFP_FLAG_PT_SHIFT;
		if (wavelength == SFP_WAVELENGTH_LL1550)
			flag |= SFP_FLAG_PT_LWLASER_LL1550 << SFP_FLAG_PT_SHIFT;
	}
	/* check if its SFP+ */
	flag |= ((page_a0[SSF_IDENTIFIER] == SFF_PG0_IDENT_SFP) ?
			SFP_FLAG_CT_SFP_PLUS : SFP_FLAG_CT_UNKNOWN)
					<< SFP_FLAG_CT_SHIFT;

	/* check if its OPTICAL */
	flag |= ((page_a0[SSF_CONNECTOR] == SFF_PG0_CONNECTOR_LC) ?
			SFP_FLAG_IS_OPTICAL_PORT : 0)
					<< SFP_FLAG_IS_OPTICAL_SHIFT;

	temperature = (page_a2[SFF_TEMPERATURE_B1] << 8 |
		page_a2[SFF_TEMPERATURE_B0]);
	vcc = (page_a2[SFF_VCC_B1] << 8 |
		page_a2[SFF_VCC_B0]);
	tx_power = (page_a2[SFF_TXPOWER_B1] << 8 |
		page_a2[SFF_TXPOWER_B0]);
	tx_bias = (page_a2[SFF_TX_BIAS_CURRENT_B1] << 8 |
		page_a2[SFF_TX_BIAS_CURRENT_B0]);
	rx_power = (page_a2[SFF_RXPOWER_B1] << 8 |
		page_a2[SFF_RXPOWER_B0]);
	desc->sfp_info.temperature = cpu_to_be16(temperature);
	desc->sfp_info.rx_power = cpu_to_be16(rx_power);
	desc->sfp_info.tx_bias = cpu_to_be16(tx_bias);
	desc->sfp_info.tx_power = cpu_to_be16(tx_power);
	desc->sfp_info.vcc = cpu_to_be16(vcc);

	desc->sfp_info.flags = cpu_to_be16(flag);
	desc->length = cpu_to_be32(sizeof(desc->sfp_info));

	return sizeof(struct fc_rdp_sfp_desc);
}