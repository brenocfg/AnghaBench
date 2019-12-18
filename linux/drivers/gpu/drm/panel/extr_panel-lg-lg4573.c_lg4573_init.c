#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct lg4573 {TYPE_1__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int lg4573_display_mode_settings (struct lg4573*) ; 
 int lg4573_gamma_settings (struct lg4573*) ; 
 int lg4573_power_settings (struct lg4573*) ; 

__attribute__((used)) static int lg4573_init(struct lg4573 *ctx)
{
	int ret;

	dev_dbg(ctx->panel.dev, "initializing LCD\n");

	ret = lg4573_display_mode_settings(ctx);
	if (ret)
		return ret;

	ret = lg4573_power_settings(ctx);
	if (ret)
		return ret;

	return lg4573_gamma_settings(ctx);
}