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
struct lgdt3306a_state {int dummy; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*) ; 
 int /*<<< orphan*/  kfree (struct lgdt3306a_state*) ; 

__attribute__((used)) static void lgdt3306a_release(struct dvb_frontend *fe)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("\n");
	kfree(state);
}