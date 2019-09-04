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
typedef  scalar_t__ u8 ;
struct serio {int dummy; } ;

/* Variables and functions */
 int serio_write (struct serio*,scalar_t__ const) ; 

__attribute__((used)) static int wacom_send(struct serio *serio, const u8 *command)
{
	int err = 0;

	for (; !err && *command; command++)
		err = serio_write(serio, *command);

	return err;
}