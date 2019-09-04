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
typedef  enum bp_encoder_control_action { ____Placeholder_bp_encoder_control_action } bp_encoder_control_action ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DISABLE ; 
 int /*<<< orphan*/  ATOM_ENABLE ; 
 int /*<<< orphan*/  ATOM_ENCODER_CMD_STREAM_SETUP ; 
 int /*<<< orphan*/  ATOM_ENCODER_INIT ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  ENCODER_CONTROL_DISABLE 131 
#define  ENCODER_CONTROL_ENABLE 130 
#define  ENCODER_CONTROL_INIT 129 
#define  ENCODER_CONTROL_SETUP 128 

__attribute__((used)) static uint8_t encoder_action_to_atom(enum bp_encoder_control_action action)
{
	uint8_t atom_action = 0;

	switch (action) {
	case ENCODER_CONTROL_ENABLE:
		atom_action = ATOM_ENABLE;
		break;
	case ENCODER_CONTROL_DISABLE:
		atom_action = ATOM_DISABLE;
		break;
	case ENCODER_CONTROL_SETUP:
		atom_action = ATOM_ENCODER_CMD_STREAM_SETUP;
		break;
	case ENCODER_CONTROL_INIT:
		atom_action = ATOM_ENCODER_INIT;
		break;
	default:
		BREAK_TO_DEBUGGER(); /* Unhandle action in driver.!! */
		break;
	}

	return atom_action;
}