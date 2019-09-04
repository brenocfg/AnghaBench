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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct af9015_state {int /*<<< orphan*/  regmap; int /*<<< orphan*/  fe_mutex; } ;

/* Variables and functions */
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int af9015_init(struct dvb_usb_device *d)
{
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret;

	dev_dbg(&intf->dev, "\n");

	mutex_init(&state->fe_mutex);

	/* init RC canary */
	ret = regmap_write(state->regmap, 0x98e9, 0xff);
	if (ret)
		goto error;

error:
	return ret;
}