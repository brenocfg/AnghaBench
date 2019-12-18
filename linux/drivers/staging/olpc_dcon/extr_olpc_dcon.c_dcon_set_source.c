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
struct dcon_priv {int pending_src; int curr_src; int /*<<< orphan*/  switch_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dcon_set_source(struct dcon_priv *dcon, int arg)
{
	if (dcon->pending_src == arg)
		return;

	dcon->pending_src = arg;

	if (dcon->curr_src != arg)
		schedule_work(&dcon->switch_source);
}