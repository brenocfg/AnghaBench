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
typedef  int u32 ;

/* Variables and functions */
#define  TP_HKEY_EV_BRGHT_CHANGED 134 
#define  TP_HKEY_EV_LID_CLOSE 133 
#define  TP_HKEY_EV_LID_OPEN 132 
#define  TP_HKEY_EV_PEN_INSERTED 131 
#define  TP_HKEY_EV_PEN_REMOVED 130 
#define  TP_HKEY_EV_TABLET_NOTEBOOK 129 
#define  TP_HKEY_EV_TABLET_TABLET 128 
 int /*<<< orphan*/  hotkey_tablet_mode_notify_change () ; 
 int /*<<< orphan*/  tpacpi_input_send_tabletsw () ; 

__attribute__((used)) static bool hotkey_notify_usrevent(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{
	/* 0x5000-0x5FFF: human interface helpers */
	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	switch (hkey) {
	case TP_HKEY_EV_PEN_INSERTED:  /* X61t: tablet pen inserted into bay */
	case TP_HKEY_EV_PEN_REMOVED:   /* X61t: tablet pen removed from bay */
		return true;

	case TP_HKEY_EV_TABLET_TABLET:   /* X41t-X61t: tablet mode */
	case TP_HKEY_EV_TABLET_NOTEBOOK: /* X41t-X61t: normal mode */
		tpacpi_input_send_tabletsw();
		hotkey_tablet_mode_notify_change();
		*send_acpi_ev = false;
		return true;

	case TP_HKEY_EV_LID_CLOSE:	/* Lid closed */
	case TP_HKEY_EV_LID_OPEN:	/* Lid opened */
	case TP_HKEY_EV_BRGHT_CHANGED:	/* brightness changed */
		/* do not propagate these events */
		*ignore_acpi_ev = true;
		return true;

	default:
		return false;
	}
}