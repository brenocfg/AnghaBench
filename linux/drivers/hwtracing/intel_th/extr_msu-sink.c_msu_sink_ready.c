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
struct sg_table {int dummy; } ;
struct msu_sink_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_th_msc_window_unlock (int /*<<< orphan*/ ,struct sg_table*) ; 

__attribute__((used)) static int msu_sink_ready(void *data, struct sg_table *sgt, size_t bytes)
{
	struct msu_sink_private *priv = data;

	intel_th_msc_window_unlock(priv->dev, sgt);

	return 0;
}