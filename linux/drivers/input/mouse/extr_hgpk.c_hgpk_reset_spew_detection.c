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
struct hgpk_data {int /*<<< orphan*/  spew_flag; scalar_t__ y_tally; scalar_t__ x_tally; scalar_t__ dupe_count; scalar_t__ spew_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_SPEW ; 

__attribute__((used)) static void hgpk_reset_spew_detection(struct hgpk_data *priv)
{
	priv->spew_count = 0;
	priv->dupe_count = 0;
	priv->x_tally = 0;
	priv->y_tally = 0;
	priv->spew_flag = NO_SPEW;
}