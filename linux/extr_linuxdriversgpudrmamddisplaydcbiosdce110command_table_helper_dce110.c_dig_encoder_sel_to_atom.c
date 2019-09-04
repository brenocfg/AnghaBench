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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGA_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGB_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGC_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGD_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGE_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGF_SEL ; 
 int /*<<< orphan*/  ATOM_TRANMSITTER_V5__DIGG_SEL ; 
#define  ENGINE_ID_DIGA 135 
#define  ENGINE_ID_DIGB 134 
#define  ENGINE_ID_DIGC 133 
#define  ENGINE_ID_DIGD 132 
#define  ENGINE_ID_DIGE 131 
#define  ENGINE_ID_DIGF 130 
#define  ENGINE_ID_DIGG 129 
#define  ENGINE_ID_UNKNOWN 128 

__attribute__((used)) static uint8_t dig_encoder_sel_to_atom(enum engine_id id)
{
	uint8_t atom_dig_encoder_sel = 0;

	switch (id) {
	case ENGINE_ID_DIGA:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGA_SEL;
		break;
	case ENGINE_ID_DIGB:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGB_SEL;
		break;
	case ENGINE_ID_DIGC:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGC_SEL;
		break;
	case ENGINE_ID_DIGD:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGD_SEL;
		break;
	case ENGINE_ID_DIGE:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGE_SEL;
		break;
	case ENGINE_ID_DIGF:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGF_SEL;
		break;
	case ENGINE_ID_DIGG:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGG_SEL;
		break;
	case ENGINE_ID_UNKNOWN:
		 /* No DIG_FRONT is associated to DIG_BACKEND */
		atom_dig_encoder_sel = 0;
		break;
	default:
		atom_dig_encoder_sel = ATOM_TRANMSITTER_V5__DIGA_SEL;
		break;
	}

	return 0;
}