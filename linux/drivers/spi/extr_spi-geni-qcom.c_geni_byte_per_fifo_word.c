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
struct spi_geni_master {int fifo_width_bits; int cur_bits_per_word; } ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,unsigned int) ; 
 unsigned int roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int geni_byte_per_fifo_word(struct spi_geni_master *mas)
{
	/*
	 * Calculate how many bytes we'll put in each FIFO word.  If the
	 * transfer words don't pack cleanly into a FIFO word we'll just put
	 * one transfer word in each FIFO word.  If they do pack we'll pack 'em.
	 */
	if (mas->fifo_width_bits % mas->cur_bits_per_word)
		return roundup_pow_of_two(DIV_ROUND_UP(mas->cur_bits_per_word,
						       BITS_PER_BYTE));

	return mas->fifo_width_bits / BITS_PER_BYTE;
}