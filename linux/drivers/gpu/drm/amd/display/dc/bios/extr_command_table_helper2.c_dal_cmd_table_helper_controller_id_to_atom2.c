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
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_CRTC1 ; 
 int /*<<< orphan*/  ATOM_CRTC2 ; 
 int /*<<< orphan*/  ATOM_CRTC3 ; 
 int /*<<< orphan*/  ATOM_CRTC4 ; 
 int /*<<< orphan*/  ATOM_CRTC5 ; 
 int /*<<< orphan*/  ATOM_CRTC6 ; 
 int /*<<< orphan*/  ATOM_CRTC_INVALID ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  CONTROLLER_ID_D0 134 
#define  CONTROLLER_ID_D1 133 
#define  CONTROLLER_ID_D2 132 
#define  CONTROLLER_ID_D3 131 
#define  CONTROLLER_ID_D4 130 
#define  CONTROLLER_ID_D5 129 
#define  CONTROLLER_ID_UNDEFINED 128 

bool dal_cmd_table_helper_controller_id_to_atom2(
	enum controller_id id,
	uint8_t *atom_id)
{
	if (atom_id == NULL) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	switch (id) {
	case CONTROLLER_ID_D0:
		*atom_id = ATOM_CRTC1;
		return true;
	case CONTROLLER_ID_D1:
		*atom_id = ATOM_CRTC2;
		return true;
	case CONTROLLER_ID_D2:
		*atom_id = ATOM_CRTC3;
		return true;
	case CONTROLLER_ID_D3:
		*atom_id = ATOM_CRTC4;
		return true;
	case CONTROLLER_ID_D4:
		*atom_id = ATOM_CRTC5;
		return true;
	case CONTROLLER_ID_D5:
		*atom_id = ATOM_CRTC6;
		return true;
	/* TODO :case CONTROLLER_ID_UNDERLAY0:
		*atom_id = ATOM_UNDERLAY_PIPE0;
		return true;
	*/
	case CONTROLLER_ID_UNDEFINED:
		*atom_id = ATOM_CRTC_INVALID;
		return true;
	default:
		/* Wrong controller id */
		BREAK_TO_DEBUGGER();
		return false;
	}
}