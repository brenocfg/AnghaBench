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
struct zd_rf {int update_channel_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct zd_rf*,int /*<<< orphan*/ ,int) ; 

void zd_rf_init(struct zd_rf *rf)
{
	memset(rf, 0, sizeof(*rf));

	/* default to update channel integration, as almost all RF's do want
	 * this */
	rf->update_channel_int = 1;
}