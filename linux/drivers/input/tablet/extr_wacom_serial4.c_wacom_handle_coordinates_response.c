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
struct wacom {TYPE_1__* dev; int /*<<< orphan*/  max_y; int /*<<< orphan*/  max_x; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wacom_handle_coordinates_response(struct wacom *wacom)
{
	int r;

	dev_dbg(&wacom->dev->dev, "Coordinates string: %s\n", wacom->data);
	r = sscanf(wacom->data, "~C%u,%u", &wacom->max_x, &wacom->max_y);
	if (r != 2)
		dev_warn(&wacom->dev->dev, "could not get max coordinates\n");
}