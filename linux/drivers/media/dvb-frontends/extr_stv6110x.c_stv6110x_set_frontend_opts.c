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
struct stv6110x_state {TYPE_2__* frontend; } ;
struct TYPE_3__ {int /*<<< orphan*/  tuner_ops; } ;
struct TYPE_4__ {TYPE_1__ ops; struct stv6110x_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv6110x_ops ; 

__attribute__((used)) static void stv6110x_set_frontend_opts(struct stv6110x_state *stv6110x)
{
	stv6110x->frontend->tuner_priv		= stv6110x;
	stv6110x->frontend->ops.tuner_ops	= stv6110x_ops;
}