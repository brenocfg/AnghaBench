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
struct wacom {scalar_t__ max_y; scalar_t__ max_x; scalar_t__ res_y; scalar_t__ res_x; } ;
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_CONFIGURATION_STRING ; 
 int /*<<< orphan*/  REQUEST_MAX_COORDINATES ; 
 int /*<<< orphan*/  REQUEST_MODEL_AND_ROM_VERSION ; 
 int wacom_send_and_wait (struct wacom*,struct serio*,int /*<<< orphan*/ ,char*) ; 
 int wacom_send_setup_string (struct wacom*,struct serio*) ; 

__attribute__((used)) static int wacom_setup(struct wacom *wacom, struct serio *serio)
{
	int err;

	/* Note that setting the link speed is the job of inputattach.
	 * We assume that reset negotiation has already happened,
	 * here. */
	err = wacom_send_and_wait(wacom, serio, REQUEST_MODEL_AND_ROM_VERSION,
				  "model and version");
	if (err)
		return err;

	if (!(wacom->res_x && wacom->res_y)) {
		err = wacom_send_and_wait(wacom, serio,
					  REQUEST_CONFIGURATION_STRING,
					  "configuration string");
		if (err)
			return err;
	}

	if (!(wacom->max_x && wacom->max_y)) {
		err = wacom_send_and_wait(wacom, serio,
					  REQUEST_MAX_COORDINATES,
					  "coordinates string");
		if (err)
			return err;
	}

	return wacom_send_setup_string(wacom, serio);
}