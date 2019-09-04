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
struct encx24j600_context {int bank; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int BANK_SELECT (int) ; 
 int spi_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int encx24j600_switch_bank(struct encx24j600_context *ctx,
				  int bank)
{
	int ret = 0;
	int bank_opcode = BANK_SELECT(bank);

	ret = spi_write(ctx->spi, &bank_opcode, 1);
	if (ret == 0)
		ctx->bank = bank;

	return ret;
}