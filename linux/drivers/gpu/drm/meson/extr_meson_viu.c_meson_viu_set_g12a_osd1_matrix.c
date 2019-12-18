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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_COEF00_01 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_COEF02_10 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_COEF11_12 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_COEF20_21 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_COEF22 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_EN_CTRL ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_OFFSET0_1 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_OFFSET2 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_PRE_OFFSET0_1 ; 
 int /*<<< orphan*/  VPP_WRAP_OSD1_MATRIX_PRE_OFFSET2 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_viu_set_g12a_osd1_matrix(struct meson_drm *priv,
					   int *m, bool csc_on)
{
	/* VPP WRAP OSD1 matrix */
	writel(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET0_1));
	writel(m[2] & 0xfff,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET2));
	writel(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF00_01));
	writel(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF02_10));
	writel(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF11_12));
	writel(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_COEF20_21));
	writel((m[11] & 0x1fff) << 16,
		priv->io_base +	_REG(VPP_WRAP_OSD1_MATRIX_COEF22));

	writel(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_OFFSET0_1));
	writel(m[20] & 0xfff,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_OFFSET2));

	writel_bits_relaxed(BIT(0), csc_on ? BIT(0) : 0,
		priv->io_base + _REG(VPP_WRAP_OSD1_MATRIX_EN_CTRL));
}