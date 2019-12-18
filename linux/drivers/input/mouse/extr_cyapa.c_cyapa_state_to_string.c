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
struct cyapa {int state; } ;

/* Variables and functions */
#define  CYAPA_STATE_BL_ACTIVE 135 
#define  CYAPA_STATE_BL_BUSY 134 
#define  CYAPA_STATE_BL_IDLE 133 
#define  CYAPA_STATE_GEN5_APP 132 
#define  CYAPA_STATE_GEN5_BL 131 
#define  CYAPA_STATE_GEN6_APP 130 
#define  CYAPA_STATE_GEN6_BL 129 
#define  CYAPA_STATE_OP 128 

__attribute__((used)) static char *cyapa_state_to_string(struct cyapa *cyapa)
{
	switch (cyapa->state) {
	case CYAPA_STATE_BL_BUSY:
		return "bootloader busy";
	case CYAPA_STATE_BL_IDLE:
		return "bootloader idle";
	case CYAPA_STATE_BL_ACTIVE:
		return "bootloader active";
	case CYAPA_STATE_GEN5_BL:
	case CYAPA_STATE_GEN6_BL:
		return "bootloader";
	case CYAPA_STATE_OP:
	case CYAPA_STATE_GEN5_APP:
	case CYAPA_STATE_GEN6_APP:
		return "operational";  /* Normal valid state. */
	default:
		return "invalid mode";
	}
}