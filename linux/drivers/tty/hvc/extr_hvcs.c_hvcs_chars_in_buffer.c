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
struct tty_struct {struct hvcs_struct* driver_data; } ;
struct hvcs_struct {int chars_in_buffer; } ;

/* Variables and functions */

__attribute__((used)) static int hvcs_chars_in_buffer(struct tty_struct *tty)
{
	struct hvcs_struct *hvcsd = tty->driver_data;

	return hvcsd->chars_in_buffer;
}