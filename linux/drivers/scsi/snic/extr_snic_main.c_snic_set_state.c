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
struct snic {int /*<<< orphan*/  state; int /*<<< orphan*/  shost; } ;
typedef  enum snic_state { ____Placeholder_snic_state } snic_state ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int snic_get_state (struct snic*) ; 
 int /*<<< orphan*/  snic_state_to_str (int) ; 

void
snic_set_state(struct snic *snic, enum snic_state state)
{
	SNIC_HOST_INFO(snic->shost, "snic state change from %s to %s\n",
		       snic_state_to_str(snic_get_state(snic)),
		       snic_state_to_str(state));

	atomic_set(&snic->state, state);
}