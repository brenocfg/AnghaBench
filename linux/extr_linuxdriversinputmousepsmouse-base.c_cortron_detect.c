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
struct psmouse {char* vendor; char* name; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  keybit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_SIDE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cortron_detect(struct psmouse *psmouse, bool set_properties)
{
	if (set_properties) {
		psmouse->vendor = "Cortron";
		psmouse->name = "PS/2 Trackball";

		__set_bit(BTN_MIDDLE, psmouse->dev->keybit);
		__set_bit(BTN_SIDE, psmouse->dev->keybit);
	}

	return 0;
}