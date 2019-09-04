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
struct l64781_state {int dummy; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;

/* Variables and functions */
 int l64781_writereg (struct l64781_state*,int,int) ; 

__attribute__((used)) static int l64781_sleep(struct dvb_frontend* fe)
{
	struct l64781_state* state = fe->demodulator_priv;

	/* Power down */
	return l64781_writereg (state, 0x3e, 0x5a);
}