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
struct tty_driver {int dummy; } ;
struct console {size_t index; } ;

/* Variables and functions */
 struct tty_driver* hvc_driver ; 
 int* vtermnos ; 

__attribute__((used)) static struct tty_driver *hvc_console_device(struct console *c, int *index)
{
	if (vtermnos[c->index] == -1)
		return NULL;

	*index = c->index;
	return hvc_driver;
}