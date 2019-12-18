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
 scalar_t__ const MSGEND ; 
 scalar_t__ const MSGESC ; 
 scalar_t__ const MSGOFFSET ; 
 scalar_t__ const MSGSTART ; 
 int serio_write (struct serio*,scalar_t__ const) ; 

__attribute__((used)) static int pulse8_send(struct serio *serio, const u8 *command, u8 cmd_len)
{
	int err = 0;

	err = serio_write(serio, MSGSTART);
	if (err)
		return err;
	for (; !err && cmd_len; command++, cmd_len--) {
		if (*command >= MSGESC) {
			err = serio_write(serio, MSGESC);
			if (!err)
				err = serio_write(serio, *command - MSGOFFSET);
		} else {
			err = serio_write(serio, *command);
		}
	}
	if (!err)
		err = serio_write(serio, MSGEND);

	return err;
}