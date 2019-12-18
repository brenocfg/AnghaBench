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
typedef  unsigned int u32 ;
typedef  int u16 ;
struct geni_se {scalar_t__ base; } ;
struct spi_geni_master {unsigned int fifo_width_bits; struct geni_se se; } ;

/* Variables and functions */
 unsigned int MIN_WORD_LEN ; 
 scalar_t__ SE_SPI_WORD_LEN ; 
 int SPI_LSB_FIRST ; 
 unsigned int WORD_LEN_MSK ; 
 int /*<<< orphan*/  geni_se_config_packing (struct geni_se*,unsigned int,unsigned int,int,int,int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void spi_setup_word_len(struct spi_geni_master *mas, u16 mode,
					unsigned int bits_per_word)
{
	unsigned int pack_words;
	bool msb_first = (mode & SPI_LSB_FIRST) ? false : true;
	struct geni_se *se = &mas->se;
	u32 word_len;

	word_len = readl(se->base + SE_SPI_WORD_LEN);

	/*
	 * If bits_per_word isn't a byte aligned value, set the packing to be
	 * 1 SPI word per FIFO word.
	 */
	if (!(mas->fifo_width_bits % bits_per_word))
		pack_words = mas->fifo_width_bits / bits_per_word;
	else
		pack_words = 1;
	word_len &= ~WORD_LEN_MSK;
	word_len |= ((bits_per_word - MIN_WORD_LEN) & WORD_LEN_MSK);
	geni_se_config_packing(&mas->se, bits_per_word, pack_words, msb_first,
								true, true);
	writel(word_len, se->base + SE_SPI_WORD_LEN);
}