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
typedef  enum viu_matrix_sel_e { ____Placeholder_viu_matrix_sel_e } viu_matrix_sel_e ;

/* Variables and functions */
 int BIT (int) ; 
 int VIU_MATRIX_OSD ; 
 int VIU_MATRIX_OSD_EOTF ; 
 scalar_t__ VIU_OSD1_EOTF_CTL ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF00_01 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF02_10 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF11_12 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF20_21 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF22_30 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF31_32 ; 
 scalar_t__ VIU_OSD1_MATRIX_COEF40_41 ; 
 scalar_t__ VIU_OSD1_MATRIX_COLMOD_COEF42 ; 
 scalar_t__ VIU_OSD1_MATRIX_CTRL ; 
 scalar_t__ VIU_OSD1_MATRIX_OFFSET0_1 ; 
 scalar_t__ VIU_OSD1_MATRIX_OFFSET2 ; 
 scalar_t__ VIU_OSD1_MATRIX_PRE_OFFSET0_1 ; 
 scalar_t__ VIU_OSD1_MATRIX_PRE_OFFSET2 ; 
 scalar_t__ _REG (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 

__attribute__((used)) static void meson_viu_set_osd_matrix(struct meson_drm *priv,
				     enum viu_matrix_sel_e m_select,
			      int *m, bool csc_on)
{
	if (m_select == VIU_MATRIX_OSD) {
		/* osd matrix, VIU_MATRIX_0 */
		writel(((m[0] & 0xfff) << 16) | (m[1] & 0xfff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_PRE_OFFSET0_1));
		writel(m[2] & 0xfff,
			priv->io_base + _REG(VIU_OSD1_MATRIX_PRE_OFFSET2));
		writel(((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF00_01));
		writel(((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF02_10));
		writel(((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF11_12));
		writel(((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_COEF20_21));

		if (m[21]) {
			writel(((m[11] & 0x1fff) << 16) | (m[12] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF22_30));
			writel(((m[13] & 0x1fff) << 16) | (m[14] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF31_32));
			writel(((m[15] & 0x1fff) << 16) | (m[16] & 0x1fff),
				priv->io_base +
					_REG(VIU_OSD1_MATRIX_COEF40_41));
			writel(m[17] & 0x1fff, priv->io_base +
				_REG(VIU_OSD1_MATRIX_COLMOD_COEF42));
		} else
			writel((m[11] & 0x1fff) << 16, priv->io_base +
				_REG(VIU_OSD1_MATRIX_COEF22_30));

		writel(((m[18] & 0xfff) << 16) | (m[19] & 0xfff),
			priv->io_base + _REG(VIU_OSD1_MATRIX_OFFSET0_1));
		writel(m[20] & 0xfff,
			priv->io_base + _REG(VIU_OSD1_MATRIX_OFFSET2));

		writel_bits_relaxed(3 << 30, m[21] << 30,
			priv->io_base + _REG(VIU_OSD1_MATRIX_COLMOD_COEF42));
		writel_bits_relaxed(7 << 16, m[22] << 16,
			priv->io_base + _REG(VIU_OSD1_MATRIX_COLMOD_COEF42));

		/* 23 reserved for clipping control */
		writel_bits_relaxed(BIT(0), csc_on ? BIT(0) : 0,
			priv->io_base + _REG(VIU_OSD1_MATRIX_CTRL));
		writel_bits_relaxed(BIT(1), 0,
			priv->io_base + _REG(VIU_OSD1_MATRIX_CTRL));
	} else if (m_select == VIU_MATRIX_OSD_EOTF) {
		int i;

		/* osd eotf matrix, VIU_MATRIX_OSD_EOTF */
		for (i = 0; i < 5; i++)
			writel(((m[i * 2] & 0x1fff) << 16) |
				(m[i * 2 + 1] & 0x1fff), priv->io_base +
				_REG(VIU_OSD1_EOTF_CTL + i + 1));

		writel_bits_relaxed(BIT(30), csc_on ? BIT(30) : 0,
			priv->io_base + _REG(VIU_OSD1_EOTF_CTL));
		writel_bits_relaxed(BIT(31), csc_on ? BIT(31) : 0,
			priv->io_base + _REG(VIU_OSD1_EOTF_CTL));
	}
}