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
struct mcde {int regs; int /*<<< orphan*/  dev; } ;
typedef  enum mcde_extsrc { ____Placeholder_mcde_extsrc } mcde_extsrc ;

/* Variables and functions */
#define  DRM_FORMAT_ABGR4444 152 
#define  DRM_FORMAT_ABGR8888 151 
#define  DRM_FORMAT_ARGB4444 150 
#define  DRM_FORMAT_ARGB8888 149 
#define  DRM_FORMAT_BGR565 148 
#define  DRM_FORMAT_BGR888 147 
#define  DRM_FORMAT_RGB565 146 
#define  DRM_FORMAT_RGB888 145 
#define  DRM_FORMAT_XBGR1555 144 
#define  DRM_FORMAT_XBGR4444 143 
#define  DRM_FORMAT_XBGR8888 142 
#define  DRM_FORMAT_XRGB1555 141 
#define  DRM_FORMAT_XRGB4444 140 
#define  DRM_FORMAT_XRGB8888 139 
#define  DRM_FORMAT_YUV422 138 
 int EINVAL ; 
 int MCDE_EXTSRC0CONF ; 
 int MCDE_EXTSRC0CR ; 
 int MCDE_EXTSRC1CONF ; 
 int MCDE_EXTSRC1CR ; 
 int MCDE_EXTSRC2CONF ; 
 int MCDE_EXTSRC2CR ; 
 int MCDE_EXTSRC3CONF ; 
 int MCDE_EXTSRC3CR ; 
 int MCDE_EXTSRC4CONF ; 
 int MCDE_EXTSRC4CR ; 
 int MCDE_EXTSRC5CONF ; 
 int MCDE_EXTSRC5CR ; 
 int MCDE_EXTSRC6CONF ; 
 int MCDE_EXTSRC6CR ; 
 int MCDE_EXTSRC7CONF ; 
 int MCDE_EXTSRC7CR ; 
 int MCDE_EXTSRC8CONF ; 
 int MCDE_EXTSRC8CR ; 
 int MCDE_EXTSRC9CONF ; 
 int MCDE_EXTSRC9CR ; 
 int MCDE_EXTSRCXCONF_BGR ; 
 int MCDE_EXTSRCXCONF_BPP_ARGB4444 ; 
 int MCDE_EXTSRCXCONF_BPP_ARGB8888 ; 
 int MCDE_EXTSRCXCONF_BPP_IRGB1555 ; 
 int MCDE_EXTSRCXCONF_BPP_RGB444 ; 
 int MCDE_EXTSRCXCONF_BPP_RGB565 ; 
 int MCDE_EXTSRCXCONF_BPP_RGB888 ; 
 int MCDE_EXTSRCXCONF_BPP_SHIFT ; 
 int MCDE_EXTSRCXCONF_BPP_XRGB8888 ; 
 int MCDE_EXTSRCXCONF_BPP_YCBCR422 ; 
 int MCDE_EXTSRCXCONF_BUF_ID_SHIFT ; 
 int MCDE_EXTSRCXCONF_BUF_NB_SHIFT ; 
 int MCDE_EXTSRCXCONF_PRI_OVLID_SHIFT ; 
 int MCDE_EXTSRCXCR_MULTIOVL_CTRL_PRIMARY ; 
 int MCDE_EXTSRCXCR_SEL_MOD_SOFTWARE_SEL ; 
#define  MCDE_EXTSRC_0 137 
#define  MCDE_EXTSRC_1 136 
#define  MCDE_EXTSRC_2 135 
#define  MCDE_EXTSRC_3 134 
#define  MCDE_EXTSRC_4 133 
#define  MCDE_EXTSRC_5 132 
#define  MCDE_EXTSRC_6 131 
#define  MCDE_EXTSRC_7 130 
#define  MCDE_EXTSRC_8 129 
#define  MCDE_EXTSRC_9 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static int mcde_configure_extsrc(struct mcde *mcde, enum mcde_extsrc src,
				 u32 format)
{
	u32 val;
	u32 conf;
	u32 cr;

	switch (src) {
	case MCDE_EXTSRC_0:
		conf = MCDE_EXTSRC0CONF;
		cr = MCDE_EXTSRC0CR;
		break;
	case MCDE_EXTSRC_1:
		conf = MCDE_EXTSRC1CONF;
		cr = MCDE_EXTSRC1CR;
		break;
	case MCDE_EXTSRC_2:
		conf = MCDE_EXTSRC2CONF;
		cr = MCDE_EXTSRC2CR;
		break;
	case MCDE_EXTSRC_3:
		conf = MCDE_EXTSRC3CONF;
		cr = MCDE_EXTSRC3CR;
		break;
	case MCDE_EXTSRC_4:
		conf = MCDE_EXTSRC4CONF;
		cr = MCDE_EXTSRC4CR;
		break;
	case MCDE_EXTSRC_5:
		conf = MCDE_EXTSRC5CONF;
		cr = MCDE_EXTSRC5CR;
		break;
	case MCDE_EXTSRC_6:
		conf = MCDE_EXTSRC6CONF;
		cr = MCDE_EXTSRC6CR;
		break;
	case MCDE_EXTSRC_7:
		conf = MCDE_EXTSRC7CONF;
		cr = MCDE_EXTSRC7CR;
		break;
	case MCDE_EXTSRC_8:
		conf = MCDE_EXTSRC8CONF;
		cr = MCDE_EXTSRC8CR;
		break;
	case MCDE_EXTSRC_9:
		conf = MCDE_EXTSRC9CONF;
		cr = MCDE_EXTSRC9CR;
		break;
	}

	/*
	 * Configure external source 0 one buffer (buffer 0)
	 * primary overlay ID 0.
	 * From mcde_hw.c ovly_update_registers() in the vendor tree
	 */
	val = 0 << MCDE_EXTSRCXCONF_BUF_ID_SHIFT;
	val |= 1 << MCDE_EXTSRCXCONF_BUF_NB_SHIFT;
	val |= 0 << MCDE_EXTSRCXCONF_PRI_OVLID_SHIFT;
	/*
	 * MCDE has inverse semantics from DRM on RBG/BGR which is why
	 * all the modes are inversed here.
	 */
	switch (format) {
	case DRM_FORMAT_ARGB8888:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_ABGR8888:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_XRGB8888:
		val |= MCDE_EXTSRCXCONF_BPP_XRGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_XBGR8888:
		val |= MCDE_EXTSRCXCONF_BPP_XRGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_RGB888:
		val |= MCDE_EXTSRCXCONF_BPP_RGB888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_BGR888:
		val |= MCDE_EXTSRCXCONF_BPP_RGB888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_ARGB4444:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB4444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_ABGR4444:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB4444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_XRGB4444:
		val |= MCDE_EXTSRCXCONF_BPP_RGB444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_XBGR4444:
		val |= MCDE_EXTSRCXCONF_BPP_RGB444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_XRGB1555:
		val |= MCDE_EXTSRCXCONF_BPP_IRGB1555 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_XBGR1555:
		val |= MCDE_EXTSRCXCONF_BPP_IRGB1555 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_RGB565:
		val |= MCDE_EXTSRCXCONF_BPP_RGB565 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		break;
	case DRM_FORMAT_BGR565:
		val |= MCDE_EXTSRCXCONF_BPP_RGB565 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	case DRM_FORMAT_YUV422:
		val |= MCDE_EXTSRCXCONF_BPP_YCBCR422 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		break;
	default:
		dev_err(mcde->dev, "Unknown pixel format 0x%08x\n",
			format);
		return -EINVAL;
	}
	writel(val, mcde->regs + conf);

	/* Software select, primary */
	val = MCDE_EXTSRCXCR_SEL_MOD_SOFTWARE_SEL;
	val |= MCDE_EXTSRCXCR_MULTIOVL_CTRL_PRIMARY;
	writel(val, mcde->regs + cr);

	return 0;
}