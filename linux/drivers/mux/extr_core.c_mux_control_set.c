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
struct mux_control {int cached_state; TYPE_2__* chip; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set ) (struct mux_control*,int) ;} ;

/* Variables and functions */
 int MUX_CACHE_UNKNOWN ; 
 int stub1 (struct mux_control*,int) ; 

__attribute__((used)) static int mux_control_set(struct mux_control *mux, int state)
{
	int ret = mux->chip->ops->set(mux, state);

	mux->cached_state = ret < 0 ? MUX_CACHE_UNKNOWN : state;

	return ret;
}