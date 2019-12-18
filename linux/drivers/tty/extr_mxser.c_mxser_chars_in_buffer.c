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
struct tty_struct {struct mxser_port* driver_data; } ;
struct mxser_port {int xmit_cnt; } ;

/* Variables and functions */

__attribute__((used)) static int mxser_chars_in_buffer(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	return info->xmit_cnt;
}