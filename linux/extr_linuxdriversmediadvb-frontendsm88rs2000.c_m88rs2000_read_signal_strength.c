#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_rf_strength ) (struct dvb_frontend*,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m88rs2000_read_signal_strength(struct dvb_frontend *fe,
	u16 *strength)
{
	if (fe->ops.tuner_ops.get_rf_strength)
		fe->ops.tuner_ops.get_rf_strength(fe, strength);

	return 0;
}