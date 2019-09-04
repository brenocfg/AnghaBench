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
struct rm68200 {int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR_RATELIMITED (char*,int) ; 
 int mipi_dsi_dcs_write_buffer (struct mipi_dsi_device*,void const*,size_t) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rm68200_dcs_write_buf(struct rm68200 *ctx, const void *data,
				  size_t len)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	int err;

	err = mipi_dsi_dcs_write_buffer(dsi, data, len);
	if (err < 0)
		DRM_ERROR_RATELIMITED("MIPI DSI DCS write buffer failed: %d\n",
				      err);
}