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
struct csio_sm {int /*<<< orphan*/  sm_state; } ;
typedef  int /*<<< orphan*/  csio_sm_state_t ;

/* Variables and functions */

__attribute__((used)) static inline csio_sm_state_t
csio_get_state(void *smp)
{
	return ((struct csio_sm *)smp)->sm_state;
}