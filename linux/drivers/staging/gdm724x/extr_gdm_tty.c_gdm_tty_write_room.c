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
struct tty_struct {struct gdm* driver_data; } ;
struct gdm {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GDM_TTY_READY (struct gdm*) ; 
 int WRITE_SIZE ; 

__attribute__((used)) static int gdm_tty_write_room(struct tty_struct *tty)
{
	struct gdm *gdm = tty->driver_data;

	if (!GDM_TTY_READY(gdm))
		return -ENODEV;

	return WRITE_SIZE;
}