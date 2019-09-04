#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rc_dev {scalar_t__ allowed_protocols; TYPE_1__* input_dev; } ;
struct TYPE_2__ {int* rep; } ;

/* Variables and functions */
 scalar_t__ RC_PROTO_BIT_CEC ; 
 size_t REP_DELAY ; 
 size_t REP_PERIOD ; 
 int input_register_device (TYPE_1__*) ; 

__attribute__((used)) static int rc_setup_rx_device(struct rc_dev *dev)
{
	int rc;

	/* rc_open will be called here */
	rc = input_register_device(dev->input_dev);
	if (rc)
		return rc;

	/*
	 * Default delay of 250ms is too short for some protocols, especially
	 * since the timeout is currently set to 250ms. Increase it to 500ms,
	 * to avoid wrong repetition of the keycodes. Note that this must be
	 * set after the call to input_register_device().
	 */
	if (dev->allowed_protocols == RC_PROTO_BIT_CEC)
		dev->input_dev->rep[REP_DELAY] = 0;
	else
		dev->input_dev->rep[REP_DELAY] = 500;

	/*
	 * As a repeat event on protocols like RC-5 and NEC take as long as
	 * 110/114ms, using 33ms as a repeat period is not the right thing
	 * to do.
	 */
	dev->input_dev->rep[REP_PERIOD] = 125;

	return 0;
}