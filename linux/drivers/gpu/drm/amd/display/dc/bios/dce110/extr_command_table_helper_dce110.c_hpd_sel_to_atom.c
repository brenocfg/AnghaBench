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
typedef  int uint8_t ;
typedef  enum hpd_source_id { ____Placeholder_hpd_source_id } hpd_source_id ;

/* Variables and functions */
 int ATOM_TRANSMITTER_CONFIG_V5_HPD1_SEL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_HPD2_SEL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_HPD3_SEL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_HPD4_SEL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_HPD5_SEL ; 
 int ATOM_TRANSMITTER_CONFIG_V5_HPD6_SEL ; 
#define  HPD_SOURCEID1 134 
#define  HPD_SOURCEID2 133 
#define  HPD_SOURCEID3 132 
#define  HPD_SOURCEID4 131 
#define  HPD_SOURCEID5 130 
#define  HPD_SOURCEID6 129 
#define  HPD_SOURCEID_UNKNOWN 128 

__attribute__((used)) static uint8_t hpd_sel_to_atom(enum hpd_source_id id)
{
	uint8_t atom_hpd_sel = 0;

	switch (id) {
	case HPD_SOURCEID1:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD1_SEL;
		break;
	case HPD_SOURCEID2:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD2_SEL;
		break;
	case HPD_SOURCEID3:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD3_SEL;
		break;
	case HPD_SOURCEID4:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD4_SEL;
		break;
	case HPD_SOURCEID5:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD5_SEL;
		break;
	case HPD_SOURCEID6:
		atom_hpd_sel = ATOM_TRANSMITTER_CONFIG_V5_HPD6_SEL;
		break;
	case HPD_SOURCEID_UNKNOWN:
	default:
		atom_hpd_sel = 0;
		break;
	}
	return atom_hpd_sel >> 4;
}