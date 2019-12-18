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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tc358764 {int /*<<< orphan*/  dev; scalar_t__ error; } ;
struct mipi_dsi_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpus (int /*<<< orphan*/ *) ; 
 scalar_t__ mipi_dsi_generic_read (struct mipi_dsi_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tc358764_read(struct tc358764 *ctx, u16 addr, u32 *val)
{
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(ctx->dev);
	ssize_t ret;

	if (ctx->error)
		return;

	cpu_to_le16s(&addr);
	ret = mipi_dsi_generic_read(dsi, &addr, sizeof(addr), val, sizeof(*val));
	if (ret >= 0)
		le32_to_cpus(val);

	dev_dbg(ctx->dev, "read: %d, addr: %d\n", addr, *val);
}