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
typedef  int /*<<< orphan*/  u8 ;
struct encx24j600_context {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int /*<<< orphan*/  RBSEL ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t) ; 

int regmap_encx24j600_spi_read(void *context, u8 reg, u8 *data, size_t count)
{
	struct encx24j600_context *ctx = context;

	if (reg == RBSEL && count > 1)
		count = 1;

	return spi_write_then_read(ctx->spi, &reg, sizeof(reg), data, count);
}