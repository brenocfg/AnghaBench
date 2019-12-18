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
struct tty_struct {struct ipoctal_channel* driver_data; } ;
struct ipoctal_channel {int nb_bytes; } ;

/* Variables and functions */

__attribute__((used)) static int ipoctal_chars_in_buffer(struct tty_struct *tty)
{
	struct ipoctal_channel *channel = tty->driver_data;

	return channel->nb_bytes;
}