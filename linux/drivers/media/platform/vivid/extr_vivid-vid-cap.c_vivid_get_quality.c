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
struct vivid_dev {int tv_freq; int /*<<< orphan*/  tpg; } ;
typedef  unsigned int s32 ;
typedef  enum tpg_quality { ____Placeholder_tpg_quality } tpg_quality ;

/* Variables and functions */
 scalar_t__ TPG_QUAL_COLOR ; 
 int TPG_QUAL_GRAY ; 
 scalar_t__ TPG_QUAL_NOISE ; 
 int tpg_g_quality (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum tpg_quality vivid_get_quality(struct vivid_dev *dev, s32 *afc)
{
	unsigned freq_modulus;

	if (afc)
		*afc = 0;
	if (tpg_g_quality(&dev->tpg) == TPG_QUAL_COLOR ||
	    tpg_g_quality(&dev->tpg) == TPG_QUAL_NOISE)
		return tpg_g_quality(&dev->tpg);

	/*
	 * There is a fake channel every 6 MHz at 49.25, 55.25, etc.
	 * From +/- 0.25 MHz around the channel there is color, and from
	 * +/- 1 MHz there is grayscale (chroma is lost).
	 * Everywhere else it is just gray.
	 */
	freq_modulus = (dev->tv_freq - 676 /* (43.25-1) * 16 */) % (6 * 16);
	if (afc)
		*afc = freq_modulus - 1 * 16;
	return TPG_QUAL_GRAY;
}