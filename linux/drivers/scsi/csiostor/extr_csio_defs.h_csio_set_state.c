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
struct csio_sm {scalar_t__ sm_state; } ;
typedef  scalar_t__ csio_sm_state_t ;

/* Variables and functions */

__attribute__((used)) static inline void
csio_set_state(void *smp, void *state)
{
	((struct csio_sm *)smp)->sm_state = (csio_sm_state_t)state;
}