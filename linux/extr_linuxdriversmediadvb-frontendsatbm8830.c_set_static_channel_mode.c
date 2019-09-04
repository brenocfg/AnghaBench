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
struct atbm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,int,int) ; 

__attribute__((used)) static int set_static_channel_mode(struct atbm_state *priv)
{
	int i;

	for (i = 0; i < 5; i++)
		atbm8830_write_reg(priv, 0x099B + i, 0x08);

	atbm8830_write_reg(priv, 0x095B, 0x7F);
	atbm8830_write_reg(priv, 0x09CB, 0x01);
	atbm8830_write_reg(priv, 0x09CC, 0x7F);
	atbm8830_write_reg(priv, 0x09CD, 0x7F);
	atbm8830_write_reg(priv, 0x0E01, 0x20);

	/* For single carrier */
	atbm8830_write_reg(priv, 0x0B03, 0x0A);
	atbm8830_write_reg(priv, 0x0935, 0x10);
	atbm8830_write_reg(priv, 0x0936, 0x08);
	atbm8830_write_reg(priv, 0x093E, 0x08);
	atbm8830_write_reg(priv, 0x096E, 0x06);

	/* frame_count_max0 */
	atbm8830_write_reg(priv, 0x0B09, 0x00);
	/* frame_count_max1 */
	atbm8830_write_reg(priv, 0x0B0A, 0x08);

	return 0;
}