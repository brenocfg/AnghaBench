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
struct tda665x_state {int dummy; } ;
struct dvb_frontend {struct tda665x_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tda665x_state*) ; 

__attribute__((used)) static void tda665x_release(struct dvb_frontend *fe)
{
	struct tda665x_state *state = fe->tuner_priv;

	fe->tuner_priv = NULL;
	kfree(state);
}