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
struct dsi_data {int /*<<< orphan*/  framedone_timeout_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_handle_framedone (struct dsi_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_framedone_irq_callback(void *data)
{
	struct dsi_data *dsi = data;

	/* Note: We get FRAMEDONE when DISPC has finished sending pixels and
	 * turns itself off. However, DSI still has the pixels in its buffers,
	 * and is sending the data.
	 */

	cancel_delayed_work(&dsi->framedone_timeout_work);

	dsi_handle_framedone(dsi, 0);
}