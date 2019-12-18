#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
struct ttusb2_state {TYPE_1__ ca; } ;
struct dvb_usb_device {struct ttusb2_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_dbg (char*) ; 
 int /*<<< orphan*/  dvb_ca_en50221_release (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tt3650_ci_uninit(struct dvb_usb_device *d)
{
	struct ttusb2_state *state;

	ci_dbg("");

	if (NULL == d)
		return;

	state = d->priv;
	if (NULL == state)
		return;

	if (NULL == state->ca.data)
		return;

	dvb_ca_en50221_release(&state->ca);

	memset(&state->ca, 0, sizeof(state->ca));
}