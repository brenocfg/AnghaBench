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
struct spi_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_SPBRR ; 
 int /*<<< orphan*/  SPBRR_SIZE_BIT ; 
 int /*<<< orphan*/  pch_spi_setclr_reg (struct spi_master*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_spi_set_bits_per_word(struct spi_master *master,
				      u8 bits_per_word)
{
	if (bits_per_word == 8)
		pch_spi_setclr_reg(master, PCH_SPBRR, 0, SPBRR_SIZE_BIT);
	else
		pch_spi_setclr_reg(master, PCH_SPBRR, SPBRR_SIZE_BIT, 0);
}