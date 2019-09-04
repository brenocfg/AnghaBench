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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct lg4573 {TYPE_1__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int lg4573_spi_write_u16_array (struct lg4573*,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lg4573_display_mode_settings(struct lg4573 *ctx)
{
	static const u16 display_mode_settings[] = {
		0x703A, 0x7270, 0x70B1, 0x7208,
		0x723B, 0x720F, 0x70B2, 0x7200,
		0x72C8, 0x70B3, 0x7200, 0x70B4,
		0x7200, 0x70B5, 0x7242, 0x7210,
		0x7210, 0x7200, 0x7220, 0x70B6,
		0x720B, 0x720F, 0x723C, 0x7213,
		0x7213, 0x72E8, 0x70B7, 0x7246,
		0x7206, 0x720C, 0x7200, 0x7200,
	};

	dev_dbg(ctx->panel.dev, "transfer display mode settings\n");
	return lg4573_spi_write_u16_array(ctx, display_mode_settings,
					  ARRAY_SIZE(display_mode_settings));
}