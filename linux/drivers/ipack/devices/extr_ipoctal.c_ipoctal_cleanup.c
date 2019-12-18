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
struct tty_struct {int /*<<< orphan*/  index; struct ipoctal_channel* driver_data; } ;
struct ipoctal_channel {int dummy; } ;
struct ipoctal {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ipoctal* chan_to_ipoctal (struct ipoctal_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipack_put_carrier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipoctal_cleanup(struct tty_struct *tty)
{
	struct ipoctal_channel *channel = tty->driver_data;
	struct ipoctal *ipoctal = chan_to_ipoctal(channel, tty->index);

	/* release the carrier driver */
	ipack_put_carrier(ipoctal->dev);
}