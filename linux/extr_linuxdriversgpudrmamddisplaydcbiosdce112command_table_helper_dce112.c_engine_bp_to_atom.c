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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum engine_id { ____Placeholder_engine_id } engine_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INT_DAC1_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG1_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG2_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG3_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG4_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG5_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG6_ENCODER_ID ; 
 int /*<<< orphan*/  ASIC_INT_DIG7_ENCODER_ID ; 
#define  ENGINE_ID_DACA 135 
#define  ENGINE_ID_DIGA 134 
#define  ENGINE_ID_DIGB 133 
#define  ENGINE_ID_DIGC 132 
#define  ENGINE_ID_DIGD 131 
#define  ENGINE_ID_DIGE 130 
#define  ENGINE_ID_DIGF 129 
#define  ENGINE_ID_DIGG 128 

__attribute__((used)) static bool engine_bp_to_atom(enum engine_id id, uint32_t *atom_engine_id)
{
	bool result = false;

	if (atom_engine_id != NULL)
		switch (id) {
		case ENGINE_ID_DIGA:
			*atom_engine_id = ASIC_INT_DIG1_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGB:
			*atom_engine_id = ASIC_INT_DIG2_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGC:
			*atom_engine_id = ASIC_INT_DIG3_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGD:
			*atom_engine_id = ASIC_INT_DIG4_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGE:
			*atom_engine_id = ASIC_INT_DIG5_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGF:
			*atom_engine_id = ASIC_INT_DIG6_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DIGG:
			*atom_engine_id = ASIC_INT_DIG7_ENCODER_ID;
			result = true;
			break;
		case ENGINE_ID_DACA:
			*atom_engine_id = ASIC_INT_DAC1_ENCODER_ID;
			result = true;
			break;
		default:
			break;
		}

	return result;
}