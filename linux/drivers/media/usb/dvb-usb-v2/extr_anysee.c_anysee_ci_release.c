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
struct anysee_state {int /*<<< orphan*/  ci; scalar_t__ ci_attached; } ;

/* Variables and functions */
 struct anysee_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dvb_ca_en50221_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void anysee_ci_release(struct dvb_usb_device *d)
{
	struct anysee_state *state = d_to_priv(d);

	/* detach CI */
	if (state->ci_attached)
		dvb_ca_en50221_release(&state->ci);

	return;
}