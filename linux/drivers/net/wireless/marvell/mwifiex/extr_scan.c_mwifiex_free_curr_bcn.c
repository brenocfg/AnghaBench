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
struct mwifiex_private {int /*<<< orphan*/ * curr_bcn_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
mwifiex_free_curr_bcn(struct mwifiex_private *priv)
{
	kfree(priv->curr_bcn_buf);
	priv->curr_bcn_buf = NULL;
}