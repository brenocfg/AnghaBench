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
struct tegra_hda_format {int pcm; int sample_rate; int bits; unsigned int channels; } ;

/* Variables and functions */
 unsigned int AC_FMT_BASE_44K ; 
#define  AC_FMT_BITS_16 132 
#define  AC_FMT_BITS_20 131 
#define  AC_FMT_BITS_24 130 
#define  AC_FMT_BITS_32 129 
#define  AC_FMT_BITS_8 128 
 unsigned int AC_FMT_BITS_MASK ; 
 unsigned int AC_FMT_BITS_SHIFT ; 
 unsigned int AC_FMT_CHAN_MASK ; 
 unsigned int AC_FMT_CHAN_SHIFT ; 
 unsigned int AC_FMT_DIV_MASK ; 
 unsigned int AC_FMT_DIV_SHIFT ; 
 unsigned int AC_FMT_MULT_MASK ; 
 unsigned int AC_FMT_MULT_SHIFT ; 
 unsigned int AC_FMT_TYPE_NON_PCM ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 

void tegra_hda_parse_format(unsigned int format, struct tegra_hda_format *fmt)
{
	unsigned int mul, div, bits, channels;

	if (format & AC_FMT_TYPE_NON_PCM)
		fmt->pcm = false;
	else
		fmt->pcm = true;

	if (format & AC_FMT_BASE_44K)
		fmt->sample_rate = 44100;
	else
		fmt->sample_rate = 48000;

	mul = (format & AC_FMT_MULT_MASK) >> AC_FMT_MULT_SHIFT;
	div = (format & AC_FMT_DIV_MASK) >> AC_FMT_DIV_SHIFT;

	fmt->sample_rate *= (mul + 1) / (div + 1);

	switch (format & AC_FMT_BITS_MASK) {
	case AC_FMT_BITS_8:
		fmt->bits = 8;
		break;

	case AC_FMT_BITS_16:
		fmt->bits = 16;
		break;

	case AC_FMT_BITS_20:
		fmt->bits = 20;
		break;

	case AC_FMT_BITS_24:
		fmt->bits = 24;
		break;

	case AC_FMT_BITS_32:
		fmt->bits = 32;
		break;

	default:
		bits = (format & AC_FMT_BITS_MASK) >> AC_FMT_BITS_SHIFT;
		WARN(1, "invalid number of bits: %#x\n", bits);
		fmt->bits = 8;
		break;
	}

	channels = (format & AC_FMT_CHAN_MASK) >> AC_FMT_CHAN_SHIFT;

	/* channels are encoded as n - 1 */
	fmt->channels = channels + 1;
}