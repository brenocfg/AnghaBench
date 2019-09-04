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
struct pasid_state {int /*<<< orphan*/  count; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pasid_state (struct pasid_state*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void put_pasid_state_wait(struct pasid_state *pasid_state)
{
	atomic_dec(&pasid_state->count);
	wait_event(pasid_state->wq, !atomic_read(&pasid_state->count));
	free_pasid_state(pasid_state);
}