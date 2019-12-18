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
struct psmouse {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MOUSE_PS2_FOCALTECH ; 
 int /*<<< orphan*/  CONFIG_MOUSE_PS2_SYNAPTICS ; 
 int /*<<< orphan*/  CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PSMOUSE_ALPS ; 
 int /*<<< orphan*/  PSMOUSE_CMD_RESET_DIS ; 
 int PSMOUSE_CYPRESS ; 
 int PSMOUSE_ELANTECH ; 
 int PSMOUSE_FOCALTECH ; 
 int PSMOUSE_FSP ; 
 int PSMOUSE_GENPS ; 
 int PSMOUSE_HGPK ; 
 unsigned int PSMOUSE_IMEX ; 
 unsigned int PSMOUSE_IMPS ; 
 int PSMOUSE_LIFEBOOK ; 
 unsigned int PSMOUSE_PS2 ; 
 int PSMOUSE_PS2PP ; 
 int PSMOUSE_SYNAPTICS ; 
 int PSMOUSE_THINKPS ; 
 int PSMOUSE_TOUCHKIT_PS2 ; 
 int PSMOUSE_TRACKPOINT ; 
 int PSMOUSE_VMMOUSE ; 
 int elantech_init (struct psmouse*) ; 
 int /*<<< orphan*/  focaltech_detect ; 
 scalar_t__ focaltech_init (struct psmouse*) ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ psmouse_do_detect (int /*<<< orphan*/ ,struct psmouse*,int,int) ; 
 unsigned int psmouse_max_proto ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 scalar_t__ psmouse_try_protocol (struct psmouse*,unsigned int,unsigned int*,int,int) ; 
 int /*<<< orphan*/  synaptics_detect ; 
 int synaptics_init (struct psmouse*) ; 
 int /*<<< orphan*/  synaptics_reset (struct psmouse*) ; 

__attribute__((used)) static int psmouse_extensions(struct psmouse *psmouse,
			      unsigned int max_proto, bool set_properties)
{
	bool synaptics_hardware = false;
	int ret;

	/*
	 * Always check for focaltech, this is safe as it uses pnp-id
	 * matching.
	 */
	if (psmouse_do_detect(focaltech_detect,
			      psmouse, false, set_properties)) {
		if (max_proto > PSMOUSE_IMEX &&
		    IS_ENABLED(CONFIG_MOUSE_PS2_FOCALTECH) &&
		    (!set_properties || focaltech_init(psmouse) == 0)) {
			return PSMOUSE_FOCALTECH;
		}
		/*
		 * Restrict psmouse_max_proto so that psmouse_initialize()
		 * does not try to reset rate and resolution, because even
		 * that upsets the device.
		 * This also causes us to basically fall through to basic
		 * protocol detection, where we fully reset the mouse,
		 * and set it up as bare PS/2 protocol device.
		 */
		psmouse_max_proto = max_proto = PSMOUSE_PS2;
	}

	/*
	 * We always check for LifeBook because it does not disturb mouse
	 * (it only checks DMI information).
	 */
	if (psmouse_try_protocol(psmouse, PSMOUSE_LIFEBOOK, &max_proto,
				 set_properties, max_proto > PSMOUSE_IMEX))
		return PSMOUSE_LIFEBOOK;

	if (psmouse_try_protocol(psmouse, PSMOUSE_VMMOUSE, &max_proto,
				 set_properties, max_proto > PSMOUSE_IMEX))
		return PSMOUSE_VMMOUSE;

	/*
	 * Try Kensington ThinkingMouse (we try first, because Synaptics
	 * probe upsets the ThinkingMouse).
	 */
	if (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_THINKPS, &max_proto,
				 set_properties, true)) {
		return PSMOUSE_THINKPS;
	}

	/*
	 * Try Synaptics TouchPad. Note that probing is done even if
	 * Synaptics protocol support is disabled in config - we need to
	 * know if it is Synaptics so we can reset it properly after
	 * probing for IntelliMouse.
	 */
	if (max_proto > PSMOUSE_PS2 &&
	    psmouse_do_detect(synaptics_detect,
			      psmouse, false, set_properties)) {
		synaptics_hardware = true;

		if (max_proto > PSMOUSE_IMEX) {
			/*
			 * Try activating protocol, but check if support is
			 * enabled first, since we try detecting Synaptics
			 * even when protocol is disabled.
			 */
			if (IS_ENABLED(CONFIG_MOUSE_PS2_SYNAPTICS) ||
			    IS_ENABLED(CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS)) {
				if (!set_properties)
					return PSMOUSE_SYNAPTICS;

				ret = synaptics_init(psmouse);
				if (ret >= 0)
					return ret;
			}

			/*
			 * Some Synaptics touchpads can emulate extended
			 * protocols (like IMPS/2).  Unfortunately
			 * Logitech/Genius probes confuse some firmware
			 * versions so we'll have to skip them.
			 */
			max_proto = PSMOUSE_IMEX;
		}

		/*
		 * Make sure that touchpad is in relative mode, gestures
		 * (taps) are enabled.
		 */
		synaptics_reset(psmouse);
	}

	/*
	 * Try Cypress Trackpad. We must try it before Finger Sensing Pad
	 * because Finger Sensing Pad probe upsets some modules of Cypress
	 * Trackpads.
	 */
	if (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_CYPRESS, &max_proto,
				 set_properties, true)) {
		return PSMOUSE_CYPRESS;
	}

	/* Try ALPS TouchPad */
	if (max_proto > PSMOUSE_IMEX) {
		ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);
		if (psmouse_try_protocol(psmouse, PSMOUSE_ALPS,
					 &max_proto, set_properties, true))
			return PSMOUSE_ALPS;
	}

	/* Try OLPC HGPK touchpad */
	if (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_HGPK, &max_proto,
				 set_properties, true)) {
		return PSMOUSE_HGPK;
	}

	/* Try Elantech touchpad */
	if (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_ELANTECH,
				 &max_proto, set_properties, false)) {
		if (!set_properties)
			return PSMOUSE_ELANTECH;

		ret = elantech_init(psmouse);
		if (ret >= 0)
			return ret;
	}

	if (max_proto > PSMOUSE_IMEX) {
		if (psmouse_try_protocol(psmouse, PSMOUSE_GENPS,
					 &max_proto, set_properties, true))
			return PSMOUSE_GENPS;

		if (psmouse_try_protocol(psmouse, PSMOUSE_PS2PP,
					 &max_proto, set_properties, true))
			return PSMOUSE_PS2PP;

		if (psmouse_try_protocol(psmouse, PSMOUSE_TRACKPOINT,
					 &max_proto, set_properties, true))
			return PSMOUSE_TRACKPOINT;

		if (psmouse_try_protocol(psmouse, PSMOUSE_TOUCHKIT_PS2,
					 &max_proto, set_properties, true))
			return PSMOUSE_TOUCHKIT_PS2;
	}

	/*
	 * Try Finger Sensing Pad. We do it here because its probe upsets
	 * Trackpoint devices (causing TP_READ_ID command to time out).
	 */
	if (max_proto > PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_FSP,
				 &max_proto, set_properties, true)) {
		return PSMOUSE_FSP;
	}

	/*
	 * Reset to defaults in case the device got confused by extended
	 * protocol probes. Note that we follow up with full reset because
	 * some mice put themselves to sleep when they see PSMOUSE_RESET_DIS.
	 */
	ps2_command(&psmouse->ps2dev, NULL, PSMOUSE_CMD_RESET_DIS);
	psmouse_reset(psmouse);

	if (max_proto >= PSMOUSE_IMEX &&
	    psmouse_try_protocol(psmouse, PSMOUSE_IMEX,
				 &max_proto, set_properties, true)) {
		return PSMOUSE_IMEX;
	}

	if (max_proto >= PSMOUSE_IMPS &&
	    psmouse_try_protocol(psmouse, PSMOUSE_IMPS,
				 &max_proto, set_properties, true)) {
		return PSMOUSE_IMPS;
	}

	/*
	 * Okay, all failed, we have a standard mouse here. The number of
	 * the buttons is still a question, though. We assume 3.
	 */
	psmouse_try_protocol(psmouse, PSMOUSE_PS2,
			     &max_proto, set_properties, true);

	if (synaptics_hardware) {
		/*
		 * We detected Synaptics hardware but it did not respond to
		 * IMPS/2 probes.  We need to reset the touchpad because if
		 * there is a track point on the pass through port it could
		 * get disabled while probing for protocol extensions.
		 */
		psmouse_reset(psmouse);
	}

	return PSMOUSE_PS2;
}