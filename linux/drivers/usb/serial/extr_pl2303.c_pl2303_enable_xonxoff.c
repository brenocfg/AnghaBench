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
struct tty_struct {int dummy; } ;
struct pl2303_type_data {scalar_t__ no_autoxonxoff; } ;

/* Variables and functions */
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 int /*<<< orphan*/  I_IXON (struct tty_struct*) ; 
 int START_CHAR (struct tty_struct*) ; 
 int STOP_CHAR (struct tty_struct*) ; 

__attribute__((used)) static bool pl2303_enable_xonxoff(struct tty_struct *tty, const struct pl2303_type_data *type)
{
	if (!I_IXON(tty) || I_IXANY(tty))
		return false;

	if (START_CHAR(tty) != 0x11 || STOP_CHAR(tty) != 0x13)
		return false;

	if (type->no_autoxonxoff)
		return false;

	return true;
}