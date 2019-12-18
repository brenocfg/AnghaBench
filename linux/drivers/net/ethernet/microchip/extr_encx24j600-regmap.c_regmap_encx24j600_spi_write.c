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
struct encx24j600_context {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int encx24j600_cmdn (struct encx24j600_context*,int,int const*,size_t) ; 
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

int regmap_encx24j600_spi_write(void *context, u8 reg, const u8 *data,
				size_t count)
{
	struct encx24j600_context *ctx = context;

	if (reg < 0xc0)
		return encx24j600_cmdn(ctx, reg, data, count);

	/* SPI 1-byte command. Ignore data */
	return spi_write(ctx->spi, &reg, 1);
}