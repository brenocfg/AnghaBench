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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRIIO_LED_RUNNING ; 
 int /*<<< orphan*/  FRIIO_LED_STOPPED ; 
 int /*<<< orphan*/  fe_to_d (struct dvb_frontend*) ; 
 int friio_ext_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int friio_streaming_ctrl(struct dvb_frontend *fe, int onoff)
{
	u32 led_color;

	led_color = onoff ? FRIIO_LED_RUNNING : FRIIO_LED_STOPPED;
	return friio_ext_ctl(fe_to_d(fe), led_color, true);
}