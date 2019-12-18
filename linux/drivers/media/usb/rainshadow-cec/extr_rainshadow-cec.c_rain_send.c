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
struct rain {int /*<<< orphan*/  serio; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 int serio_write (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int rain_send(struct rain *rain, const char *command)
{
	int err = serio_write(rain->serio, '!');

	dev_dbg(rain->dev, "send: %s\n", command);
	while (!err && *command)
		err = serio_write(rain->serio, *command++);
	if (!err)
		err = serio_write(rain->serio, '~');

	return err;
}