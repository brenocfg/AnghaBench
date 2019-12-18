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
struct gve_priv {int /*<<< orphan*/  service_task; int /*<<< orphan*/  gve_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_set_do_reset (struct gve_priv*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gve_schedule_reset(struct gve_priv *priv)
{
	gve_set_do_reset(priv);
	queue_work(priv->gve_wq, &priv->service_task);
}