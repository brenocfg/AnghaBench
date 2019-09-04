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
typedef  int u8 ;
typedef  enum fman_intr_type { ____Placeholder_fman_intr_type } fman_intr_type ;
typedef  enum fman_event_modules { ____Placeholder_fman_event_modules } fman_event_modules ;

/* Variables and functions */
 int FMAN_EV_CNT ; 
 int FMAN_EV_ERR_MAC0 ; 
 int FMAN_EV_FMAN_CTRL_0 ; 
 int FMAN_EV_MAC0 ; 
 int FMAN_INTR_TYPE_ERR ; 
#define  FMAN_MOD_DUMMY_LAST 130 
#define  FMAN_MOD_FMAN_CTRL 129 
#define  FMAN_MOD_MAC 128 

__attribute__((used)) static int get_module_event(enum fman_event_modules module, u8 mod_id,
			    enum fman_intr_type intr_type)
{
	int event;

	switch (module) {
	case FMAN_MOD_MAC:
		if (intr_type == FMAN_INTR_TYPE_ERR)
			event = FMAN_EV_ERR_MAC0 + mod_id;
		else
			event = FMAN_EV_MAC0 + mod_id;
		break;
	case FMAN_MOD_FMAN_CTRL:
		if (intr_type == FMAN_INTR_TYPE_ERR)
			event = FMAN_EV_CNT;
		else
			event = (FMAN_EV_FMAN_CTRL_0 + mod_id);
		break;
	case FMAN_MOD_DUMMY_LAST:
		event = FMAN_EV_CNT;
		break;
	default:
		event = FMAN_EV_CNT;
		break;
	}

	return event;
}