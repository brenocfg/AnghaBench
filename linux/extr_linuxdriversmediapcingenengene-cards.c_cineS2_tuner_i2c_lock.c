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
struct ngene_channel {TYPE_1__* dev; } ;
struct dvb_frontend {struct ngene_channel* analog_demod_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  pll_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cineS2_tuner_i2c_lock(struct dvb_frontend *fe, int lock)
{
	struct ngene_channel *chan = fe->analog_demod_priv;

	if (lock)
		down(&chan->dev->pll_mutex);
	else
		up(&chan->dev->pll_mutex);
}