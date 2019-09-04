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
struct mt2063_state {int dummy; } ;
struct dvb_frontend {struct mt2063_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  kfree (struct mt2063_state*) ; 

__attribute__((used)) static void mt2063_release(struct dvb_frontend *fe)
{
	struct mt2063_state *state = fe->tuner_priv;

	dprintk(2, "\n");

	fe->tuner_priv = NULL;
	kfree(state);
}