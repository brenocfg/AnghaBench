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
struct il_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  ieee_rates; int /*<<< orphan*/  ieee_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_GEO_CONFIGURED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void
il_free_geos(struct il_priv *il)
{
	kfree(il->ieee_channels);
	kfree(il->ieee_rates);
	clear_bit(S_GEO_CONFIGURED, &il->status);
}