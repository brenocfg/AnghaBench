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
struct dvb_usb_device {int dummy; } ;
struct anysee_state {scalar_t__* i2c_client; } ;

/* Variables and functions */
 void anysee_ci_release (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  anysee_del_i2c_dev (struct dvb_usb_device*) ; 
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 

__attribute__((used)) static void anysee_exit(struct dvb_usb_device *d)
{
	struct anysee_state *state = d_to_priv(d);

	if (state->i2c_client[0])
		anysee_del_i2c_dev(d);

	return anysee_ci_release(d);
}