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
typedef  int u32 ;
struct stm32_spi {scalar_t__ base; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ STM32H7_SPI_CR2 ; 
 int STM32H7_SPI_CR2_TSIZE ; 
 int STM32H7_SPI_CR2_TSIZE_SHIFT ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int stm32h7_spi_number_of_data(struct stm32_spi *spi, u32 nb_words)
{
	u32 cr2_clrb = 0, cr2_setb = 0;

	if (nb_words <= (STM32H7_SPI_CR2_TSIZE >>
			 STM32H7_SPI_CR2_TSIZE_SHIFT)) {
		cr2_clrb |= STM32H7_SPI_CR2_TSIZE;
		cr2_setb = nb_words << STM32H7_SPI_CR2_TSIZE_SHIFT;
		writel_relaxed((readl_relaxed(spi->base + STM32H7_SPI_CR2) &
				~cr2_clrb) | cr2_setb,
			       spi->base + STM32H7_SPI_CR2);
	} else {
		return -EMSGSIZE;
	}

	return 0;
}