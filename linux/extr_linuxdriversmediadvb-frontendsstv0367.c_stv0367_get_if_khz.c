#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_if_frequency ) (TYPE_4__*,int*) ;} ;
struct TYPE_7__ {TYPE_2__ tuner_ops; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct stv0367_state {TYPE_1__* config; TYPE_4__ fe; scalar_t__ auto_if_khz; } ;
struct TYPE_5__ {int if_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int*) ; 

__attribute__((used)) static int stv0367_get_if_khz(struct stv0367_state *state, u32 *ifkhz)
{
	if (state->auto_if_khz && state->fe.ops.tuner_ops.get_if_frequency) {
		state->fe.ops.tuner_ops.get_if_frequency(&state->fe, ifkhz);
		*ifkhz = *ifkhz / 1000; /* hz -> khz */
	} else
		*ifkhz = state->config->if_khz;

	return 0;
}