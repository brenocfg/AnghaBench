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
struct ipu3_uapi_grid_config {int /*<<< orphan*/  block_height_log2; int /*<<< orphan*/  height; int /*<<< orphan*/  y_start; void* y_end; int /*<<< orphan*/  block_width_log2; int /*<<< orphan*/  width; int /*<<< orphan*/  x_start; void* x_end; } ;

/* Variables and functions */
 void* imgu_css_grid_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imgu_css_grid_end_calc(struct ipu3_uapi_grid_config *grid_cfg)
{
	grid_cfg->x_end = imgu_css_grid_end(grid_cfg->x_start, grid_cfg->width,
					    grid_cfg->block_width_log2);
	grid_cfg->y_end = imgu_css_grid_end(grid_cfg->y_start, grid_cfg->height,
					    grid_cfg->block_height_log2);
}