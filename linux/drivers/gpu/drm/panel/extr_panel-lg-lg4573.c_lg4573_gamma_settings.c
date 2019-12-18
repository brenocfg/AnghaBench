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

__attribute__((used)) static int lg4573_gamma_settings(struct lg4573 *ctx)
{
	static const u16 gamma_settings[] = {
		0x70D0, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D1, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
		0x70D2, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D3, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
		0x70D4, 0x7203, 0x7207, 0x7273,
		0x7235, 0x7200, 0x7201, 0x7220,
		0x7200, 0x7203, 0x70D5, 0x7203,
		0x7207, 0x7273, 0x7235, 0x7200,
		0x7201, 0x7220, 0x7200, 0x7203,
	};

	dev_dbg(ctx->panel.dev, "transfer gamma settings\n");
	return lg4573_spi_write_u16_array(ctx, gamma_settings,
					  ARRAY_SIZE(gamma_settings));
}