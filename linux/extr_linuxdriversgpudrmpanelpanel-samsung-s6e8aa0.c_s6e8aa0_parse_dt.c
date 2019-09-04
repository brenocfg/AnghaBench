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
struct s6e8aa0 {void* flip_vertical; void* flip_horizontal; int /*<<< orphan*/  height_mm; int /*<<< orphan*/  width_mm; int /*<<< orphan*/  init_delay; int /*<<< orphan*/  reset_delay; int /*<<< orphan*/  power_on_delay; int /*<<< orphan*/  vm; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int of_get_videomode (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s6e8aa0_parse_dt(struct s6e8aa0 *ctx)
{
	struct device *dev = ctx->dev;
	struct device_node *np = dev->of_node;
	int ret;

	ret = of_get_videomode(np, &ctx->vm, 0);
	if (ret < 0)
		return ret;

	of_property_read_u32(np, "power-on-delay", &ctx->power_on_delay);
	of_property_read_u32(np, "reset-delay", &ctx->reset_delay);
	of_property_read_u32(np, "init-delay", &ctx->init_delay);
	of_property_read_u32(np, "panel-width-mm", &ctx->width_mm);
	of_property_read_u32(np, "panel-height-mm", &ctx->height_mm);

	ctx->flip_horizontal = of_property_read_bool(np, "flip-horizontal");
	ctx->flip_vertical = of_property_read_bool(np, "flip-vertical");

	return 0;
}