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
struct serio {int /*<<< orphan*/  name; int /*<<< orphan*/  phys; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int device_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void serio_find_driver(struct serio *serio)
{
	int error;

	error = device_attach(&serio->dev);
	if (error < 0 && error != -EPROBE_DEFER)
		dev_warn(&serio->dev,
			 "device_attach() failed for %s (%s), error: %d\n",
			 serio->phys, serio->name, error);
}