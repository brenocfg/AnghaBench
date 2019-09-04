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

__attribute__((used)) static int lg4573_power_settings(struct lg4573 *ctx)
{
	static const u16 power_settings[] = {
		0x70C0, 0x7201, 0x7211, 0x70C3,
		0x7207, 0x7203, 0x7204, 0x7204,
		0x7204, 0x70C4, 0x7212, 0x7224,
		0x7218, 0x7218, 0x7202, 0x7249,
		0x70C5, 0x726F, 0x70C6, 0x7241,
		0x7263,
	};

	dev_dbg(ctx->panel.dev, "transfer power settings\n");
	return lg4573_spi_write_u16_array(ctx, power_settings,
					  ARRAY_SIZE(power_settings));
}