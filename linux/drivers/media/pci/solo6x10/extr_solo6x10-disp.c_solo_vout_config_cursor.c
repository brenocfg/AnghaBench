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
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_VO_CURSOR_CLR ; 
 int /*<<< orphan*/  SOLO_VO_CURSOR_CLR2 ; 
 int /*<<< orphan*/  SOLO_VO_CURSOR_MASK (int) ; 
 int /*<<< orphan*/  SOLO_VO_CURSOR_POS ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_vout_config_cursor(struct solo_dev *dev)
{
	int i;

	/* Load (blank) cursor bitmap mask (2bpp) */
	for (i = 0; i < 20; i++)
		solo_reg_write(dev, SOLO_VO_CURSOR_MASK(i), 0);

	solo_reg_write(dev, SOLO_VO_CURSOR_POS, 0);

	solo_reg_write(dev, SOLO_VO_CURSOR_CLR,
		       (0x80 << 24) | (0x80 << 16) | (0x10 << 8) | 0x80);
	solo_reg_write(dev, SOLO_VO_CURSOR_CLR2, (0xe0 << 8) | 0x80);
}