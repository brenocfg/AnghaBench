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
struct dvb_frontend {scalar_t__ tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_SLEEP ; 
 int stv6110x_set_mode (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv6110x_sleep(struct dvb_frontend *fe)
{
	if (fe->tuner_priv)
		return stv6110x_set_mode(fe, TUNER_SLEEP);

	return 0;
}