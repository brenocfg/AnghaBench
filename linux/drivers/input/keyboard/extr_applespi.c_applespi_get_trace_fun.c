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
typedef  enum applespi_evt_type { ____Placeholder_applespi_evt_type } applespi_evt_type ;
typedef  int /*<<< orphan*/  applespi_trace_fun ;

/* Variables and functions */
#define  ET_CMD_BL 133 
#define  ET_CMD_CL 132 
#define  ET_CMD_TP_INI 131 
#define  ET_RD_KEYB 130 
#define  ET_RD_TPAD 129 
#define  ET_RD_UNKN 128 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  trace_applespi_backlight_cmd ; 
 int /*<<< orphan*/  trace_applespi_caps_lock_cmd ; 
 int /*<<< orphan*/  trace_applespi_keyboard_data ; 
 int /*<<< orphan*/  trace_applespi_touchpad_data ; 
 int /*<<< orphan*/  trace_applespi_tp_ini_cmd ; 
 int /*<<< orphan*/  trace_applespi_unknown_data ; 

__attribute__((used)) static applespi_trace_fun applespi_get_trace_fun(enum applespi_evt_type type)
{
	switch (type) {
	case ET_CMD_TP_INI:
		return trace_applespi_tp_ini_cmd;
	case ET_CMD_BL:
		return trace_applespi_backlight_cmd;
	case ET_CMD_CL:
		return trace_applespi_caps_lock_cmd;
	case ET_RD_KEYB:
		return trace_applespi_keyboard_data;
	case ET_RD_TPAD:
		return trace_applespi_touchpad_data;
	case ET_RD_UNKN:
		return trace_applespi_unknown_data;
	default:
		WARN_ONCE(1, "Unknown msg type %d", type);
		return trace_applespi_unknown_data;
	}
}