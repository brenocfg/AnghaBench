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
typedef  int /*<<< orphan*/  u16 ;
struct s6e8aa0 {int error; int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int mipi_dsi_set_maximum_return_packet_size (struct mipi_dsi_device*,int /*<<< orphan*/ ) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s6e8aa0_set_maximum_return_packet_size(struct s6e8aa0 *ctx,
						   u16 size)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int ret;

	if (ctx->error < 0)
		return;

	ret = mipi_dsi_set_maximum_return_packet_size(dsi, size);
	if (ret < 0) {
		dev_err(ctx->dev,
			"error %d setting maximum return packet size to %d\n",
			ret, size);
		ctx->error = ret;
	}
}