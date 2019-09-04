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
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mal_poll_disable(struct mal_instance *mal, struct mal_commac *commac)
{
	/* Spinlock-type semantics: only one caller disable poll at a time */
	while (test_and_set_bit(MAL_COMMAC_POLL_DISABLED, &commac->flags))
		msleep(1);

	/* Synchronize with the MAL NAPI poller */
	napi_synchronize(&mal->napi);
}