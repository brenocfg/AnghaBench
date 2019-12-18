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
struct tty_struct {struct ipoctal_channel* driver_data; int /*<<< orphan*/  index; int /*<<< orphan*/  dev; } ;
struct ipoctal_channel {int /*<<< orphan*/  tty_port; } ;
struct ipoctal {int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct ipoctal* chan_to_ipoctal (struct ipoctal_channel*,int /*<<< orphan*/ ) ; 
 struct ipoctal_channel* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipack_get_carrier (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipack_put_carrier (int /*<<< orphan*/ ) ; 
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int ipoctal_open(struct tty_struct *tty, struct file *file)
{
	struct ipoctal_channel *channel = dev_get_drvdata(tty->dev);
	struct ipoctal *ipoctal = chan_to_ipoctal(channel, tty->index);
	int err;

	tty->driver_data = channel;

	if (!ipack_get_carrier(ipoctal->dev))
		return -EBUSY;

	err = tty_port_open(&channel->tty_port, tty, file);
	if (err)
		ipack_put_carrier(ipoctal->dev);

	return err;
}