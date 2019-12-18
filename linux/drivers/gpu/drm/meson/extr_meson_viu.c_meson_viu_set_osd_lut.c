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
typedef  enum viu_lut_sel_e { ____Placeholder_viu_lut_sel_e } viu_lut_sel_e ;

/* Variables and functions */
 int BIT (int) ; 
 int OSD_EOTF_LUT_SIZE ; 
 int OSD_OETF_LUT_SIZE ; 
 int VIU_LUT_OSD_EOTF ; 
 int VIU_LUT_OSD_OETF ; 
 unsigned int VIU_OSD1_EOTF_CTL ; 
 unsigned int VIU_OSD1_EOTF_LUT_ADDR_PORT ; 
 unsigned int VIU_OSD1_EOTF_LUT_DATA_PORT ; 
 unsigned int VIU_OSD1_OETF_CTL ; 
 unsigned int VIU_OSD1_OETF_LUT_ADDR_PORT ; 
 unsigned int VIU_OSD1_OETF_LUT_DATA_PORT ; 
 scalar_t__ _REG (unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 

__attribute__((used)) static void
meson_viu_set_osd_lut(struct meson_drm *priv, enum viu_lut_sel_e lut_sel,
		      unsigned int *r_map, unsigned int *g_map,
		      unsigned int *b_map, bool csc_on)
{
	unsigned int addr_port;
	unsigned int data_port;
	unsigned int ctrl_port;
	int i;

	if (lut_sel == VIU_LUT_OSD_EOTF) {
		addr_port = VIU_OSD1_EOTF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_EOTF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_EOTF_CTL;
	} else if (lut_sel == VIU_LUT_OSD_OETF) {
		addr_port = VIU_OSD1_OETF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_OETF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_OETF_CTL;
	} else
		return;

	if (lut_sel == VIU_LUT_OSD_OETF) {
		writel(0, priv->io_base + _REG(addr_port));

		for (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			writel(r_map[i * 2] | (r_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		writel(r_map[OSD_OETF_LUT_SIZE - 1] | (g_map[0] << 16),
			priv->io_base + _REG(data_port));

		for (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			writel(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				priv->io_base + _REG(data_port));

		for (i = 0; i < (OSD_OETF_LUT_SIZE / 2); i++)
			writel(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		writel(b_map[OSD_OETF_LUT_SIZE - 1],
			priv->io_base + _REG(data_port));

		if (csc_on)
			writel_bits_relaxed(0x7 << 29, 7 << 29,
					    priv->io_base + _REG(ctrl_port));
		else
			writel_bits_relaxed(0x7 << 29, 0,
					    priv->io_base + _REG(ctrl_port));
	} else if (lut_sel == VIU_LUT_OSD_EOTF) {
		writel(0, priv->io_base + _REG(addr_port));

		for (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			writel(r_map[i * 2] | (r_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		writel(r_map[OSD_EOTF_LUT_SIZE - 1] | (g_map[0] << 16),
			priv->io_base + _REG(data_port));

		for (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			writel(g_map[i * 2 + 1] | (g_map[i * 2 + 2] << 16),
				priv->io_base + _REG(data_port));

		for (i = 0; i < (OSD_EOTF_LUT_SIZE / 2); i++)
			writel(b_map[i * 2] | (b_map[i * 2 + 1] << 16),
				priv->io_base + _REG(data_port));

		writel(b_map[OSD_EOTF_LUT_SIZE - 1],
			priv->io_base + _REG(data_port));

		if (csc_on)
			writel_bits_relaxed(7 << 27, 7 << 27,
					    priv->io_base + _REG(ctrl_port));
		else
			writel_bits_relaxed(7 << 27, 0,
					    priv->io_base + _REG(ctrl_port));

		writel_bits_relaxed(BIT(31), BIT(31),
				    priv->io_base + _REG(ctrl_port));
	}
}