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
struct TYPE_2__ {scalar_t__ current_state; } ;
struct sdma_engine {TYPE_1__ state; } ;

/* Variables and functions */
 scalar_t__ sdma_state_s99_running ; 

__attribute__((used)) static inline int __sdma_running(struct sdma_engine *engine)
{
	return engine->state.current_state == sdma_state_s99_running;
}