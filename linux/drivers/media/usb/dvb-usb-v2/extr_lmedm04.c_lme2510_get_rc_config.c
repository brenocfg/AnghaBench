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
struct dvb_usb_rc {int /*<<< orphan*/  allowed_protos; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PROTO_BIT_NEC32 ; 

__attribute__((used)) static int lme2510_get_rc_config(struct dvb_usb_device *d,
	struct dvb_usb_rc *rc)
{
	rc->allowed_protos = RC_PROTO_BIT_NEC32;
	return 0;
}