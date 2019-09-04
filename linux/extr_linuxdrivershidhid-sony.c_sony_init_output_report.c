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
struct sony_sc {void (* send_output_report ) (struct sony_sc*) ;int state_worker_initialized; int /*<<< orphan*/  state_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sony_state_worker ; 

__attribute__((used)) static inline void sony_init_output_report(struct sony_sc *sc,
				void (*send_output_report)(struct sony_sc *))
{
	sc->send_output_report = send_output_report;

	if (!sc->state_worker_initialized)
		INIT_WORK(&sc->state_worker, sony_state_worker);

	sc->state_worker_initialized = 1;
}