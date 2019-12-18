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
struct mal_instance {int /*<<< orphan*/  napi; } ;
struct mal_commac {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAL_COMMAC_POLL_DISABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void mal_poll_enable(struct mal_instance *mal, struct mal_commac *commac)
{
	smp_wmb();
	clear_bit(MAL_COMMAC_POLL_DISABLED, &commac->flags);

	/* Feels better to trigger a poll here to catch up with events that
	 * may have happened on this channel while disabled. It will most
	 * probably be delayed until the next interrupt but that's mostly a
	 * non-issue in the context where this is called.
	 */
	napi_schedule(&mal->napi);
}