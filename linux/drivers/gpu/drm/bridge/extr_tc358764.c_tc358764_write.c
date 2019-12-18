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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tc358764 {scalar_t__ error; int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ mipi_dsi_generic_write (struct mipi_dsi_device*,int*,int) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc358764_write(struct tc358764 *ctx, u16 addr, u32 val)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	ssize_t ret;
	u8 data[6];

	if (ctx->error)
		return;

	data[0] = addr;
	data[1] = addr >> 8;
	data[2] = val;
	data[3] = val >> 8;
	data[4] = val >> 16;
	data[5] = val >> 24;

	ret = mipi_dsi_generic_write(dsi, data, sizeof(data));
	if (ret < 0)
		ctx->error = ret;
}