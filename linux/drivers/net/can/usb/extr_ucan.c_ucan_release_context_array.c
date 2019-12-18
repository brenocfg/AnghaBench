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
struct ucan_priv {int /*<<< orphan*/ * context_array; scalar_t__ available_tx_urbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucan_release_context_array(struct ucan_priv *up)
{
	if (!up->context_array)
		return;

	/* lock is not needed because, driver is currently opening or closing */
	up->available_tx_urbs = 0;

	kfree(up->context_array);
	up->context_array = NULL;
}