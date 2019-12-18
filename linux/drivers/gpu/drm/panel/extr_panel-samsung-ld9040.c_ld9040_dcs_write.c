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
struct ld9040 {int error; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int const*) ; 
 int ld9040_spi_write_word (struct ld9040*,int const) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ld9040_dcs_write(struct ld9040 *ctx, const u8 *data, size_t len)
{
	int ret = 0;

	if (ctx->error < 0 || len == 0)
		return;

	dev_dbg(ctx->dev, "writing dcs seq: %*ph\n", (int)len, data);
	ret = ld9040_spi_write_word(ctx, *data);

	while (!ret && --len) {
		++data;
		ret = ld9040_spi_write_word(ctx, *data | 0x100);
	}

	if (ret) {
		dev_err(ctx->dev, "error %d writing dcs seq: %*ph\n", ret,
			(int)len, data);
		ctx->error = ret;
	}

	usleep_range(300, 310);
}