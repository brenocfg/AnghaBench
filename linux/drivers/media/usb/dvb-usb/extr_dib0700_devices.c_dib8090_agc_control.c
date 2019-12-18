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
typedef  scalar_t__ u8 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  deb_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  dib0090_dcc_freq (struct dvb_frontend*,scalar_t__) ; 
 int /*<<< orphan*/  dib0090_set_dc_servo (struct dvb_frontend*,int) ; 

__attribute__((used)) static void dib8090_agc_control(struct dvb_frontend *fe, u8 restart)
{
	deb_info("AGC control callback: %i\n", restart);
	dib0090_dcc_freq(fe, restart);

	if (restart == 0) /* before AGC startup */
		dib0090_set_dc_servo(fe, 1);
}