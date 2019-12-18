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
struct asus_rfkill {int /*<<< orphan*/ * rfkill; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void asus_rfkill_terminate(struct asus_rfkill *rfk)
{
	if (!rfk->rfkill)
		return ;

	rfkill_unregister(rfk->rfkill);
	rfkill_destroy(rfk->rfkill);
	rfk->rfkill = NULL;
}