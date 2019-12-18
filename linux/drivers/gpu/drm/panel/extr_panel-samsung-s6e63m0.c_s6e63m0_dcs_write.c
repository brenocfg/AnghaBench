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
struct s6e63m0 {int error; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int const DATA_MASK ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*,int,int const*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int,int const*) ; 
 int s6e63m0_spi_write_word (struct s6e63m0*,int const) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void s6e63m0_dcs_write(struct s6e63m0 *ctx, const u8 *data, size_t len)
{
	int ret = 0;

	if (ctx->error < 0 || len == 0)
		return;

	DRM_DEV_DEBUG(ctx->dev, "writing dcs seq: %*ph\n", (int)len, data);
	ret = s6e63m0_spi_write_word(ctx, *data);

	while (!ret && --len) {
		++data;
		ret = s6e63m0_spi_write_word(ctx, *data | DATA_MASK);
	}

	if (ret) {
		DRM_DEV_ERROR(ctx->dev, "error %d writing dcs seq: %*ph\n", ret,
			      (int)len, data);
		ctx->error = ret;
	}

	usleep_range(300, 310);
}