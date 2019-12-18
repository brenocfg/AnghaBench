#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wacom {char* data; char expect; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  result; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  wacom_handle_configuration_response (struct wacom*) ; 
 int /*<<< orphan*/  wacom_handle_coordinates_response (struct wacom*) ; 
 int /*<<< orphan*/  wacom_handle_model_response (struct wacom*) ; 

__attribute__((used)) static void wacom_handle_response(struct wacom *wacom)
{
	if (wacom->data[0] != '~' || wacom->data[1] != wacom->expect) {
		dev_err(&wacom->dev->dev,
			"Wacom got an unexpected response: %s\n", wacom->data);
		wacom->result = -EIO;
	} else {
		wacom->result = 0;

		switch (wacom->data[1]) {
		case '#':
			wacom_handle_model_response(wacom);
			break;
		case 'R':
			wacom_handle_configuration_response(wacom);
			break;
		case 'C':
			wacom_handle_coordinates_response(wacom);
			break;
		}
	}

	complete(&wacom->cmd_done);
}