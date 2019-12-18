#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct imstt_par {scalar_t__ ramdac; int* cmap_regs; int /*<<< orphan*/  dc_regs; } ;
struct TYPE_8__ {int smem_len; int mmio_len; int line_length; int xpanstep; int ypanstep; int /*<<< orphan*/  id; scalar_t__ ywrapstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; int /*<<< orphan*/  accel; } ;
struct TYPE_7__ {int length; } ;
struct TYPE_10__ {int xres; int xres_virtual; int yres; int yres_virtual; int bits_per_pixel; int pixclock; TYPE_1__ green; int /*<<< orphan*/  accel_flags; } ;
struct fb_info {int flags; TYPE_2__ fix; int /*<<< orphan*/  cmap; int /*<<< orphan*/ * fbops; TYPE_4__ var; scalar_t__ screen_base; struct imstt_par* par; } ;
typedef  int __u32 ;
struct TYPE_9__ {int addr; int value; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int CMODE_32 ; 
 int CMODE_8 ; 
 int /*<<< orphan*/  CONFIG_NVRAM ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_FILLRECT ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_ACCEL_IMS_TWINTURBO ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_DIRECTCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 scalar_t__ IBM ; 
 void* INIT_BPP ; 
 void* INIT_XRES ; 
 void* INIT_YRES ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CMODE ; 
 int /*<<< orphan*/  NV_VMODE ; 
 size_t PIDXDATA ; 
 size_t PIDXHI ; 
 size_t PIDXLO ; 
 size_t PPMASK ; 
 int /*<<< orphan*/  PRC ; 
 int /*<<< orphan*/  SSR ; 
 int /*<<< orphan*/  SSTATUS ; 
 int /*<<< orphan*/  STGCTL ; 
 size_t TVPADDRW ; 
 size_t TVPIDATA ; 
 int VMODE_640_480_67 ; 
 int VMODE_MAX ; 
 int /*<<< orphan*/  compute_imstt_regvals (struct imstt_par*,int,int) ; 
 int /*<<< orphan*/  eieio () ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int getclkMHz (struct imstt_par*) ; 
 TYPE_3__* ibm_initregs ; 
 int /*<<< orphan*/  imsttfb_ops ; 
 int init_cmode ; 
 int init_vmode ; 
 scalar_t__ mac_vmode_to_var (int,int,TYPE_4__*) ; 
 scalar_t__ machine_is (int /*<<< orphan*/ ) ; 
 int nvram_read_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powermac ; 
 int /*<<< orphan*/  printk (char*,int,int,int) ; 
 int read_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  set_555 (struct imstt_par*) ; 
 int /*<<< orphan*/  set_565 (struct imstt_par*) ; 
 int /*<<< orphan*/  set_imstt_regvals (struct fb_info*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_3__* tvp_initregs ; 
 int /*<<< orphan*/  write_reg_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_imstt(struct fb_info *info)
{
	struct imstt_par *par = info->par;
	__u32 i, tmp, *ip, *end;

	tmp = read_reg_le32(par->dc_regs, PRC);
	if (par->ramdac == IBM)
		info->fix.smem_len = (tmp & 0x0004) ? 0x400000 : 0x200000;
	else
		info->fix.smem_len = 0x800000;

	ip = (__u32 *)info->screen_base;
	end = (__u32 *)(info->screen_base + info->fix.smem_len);
	while (ip < end)
		*ip++ = 0;

	/* initialize the card */
	tmp = read_reg_le32(par->dc_regs, STGCTL);
	write_reg_le32(par->dc_regs, STGCTL, tmp & ~0x1);
	write_reg_le32(par->dc_regs, SSR, 0);

	/* set default values for DAC registers */
	if (par->ramdac == IBM) {
		par->cmap_regs[PPMASK] = 0xff;
		eieio();
		par->cmap_regs[PIDXHI] = 0;
		eieio();
		for (i = 0; i < ARRAY_SIZE(ibm_initregs); i++) {
			par->cmap_regs[PIDXLO] = ibm_initregs[i].addr;
			eieio();
			par->cmap_regs[PIDXDATA] = ibm_initregs[i].value;
			eieio();
		}
	} else {
		for (i = 0; i < ARRAY_SIZE(tvp_initregs); i++) {
			par->cmap_regs[TVPADDRW] = tvp_initregs[i].addr;
			eieio();
			par->cmap_regs[TVPIDATA] = tvp_initregs[i].value;
			eieio();
		}
	}

#if defined(CONFIG_PPC_PMAC) && defined(CONFIG_PPC32)
	if (IS_REACHABLE(CONFIG_NVRAM) && machine_is(powermac)) {
		int vmode = init_vmode, cmode = init_cmode;

		if (vmode == -1) {
			vmode = nvram_read_byte(NV_VMODE);
			if (vmode <= 0 || vmode > VMODE_MAX)
				vmode = VMODE_640_480_67;
		}
		if (cmode == -1) {
			cmode = nvram_read_byte(NV_CMODE);
			if (cmode < CMODE_8 || cmode > CMODE_32)
				cmode = CMODE_8;
		}
		if (mac_vmode_to_var(vmode, cmode, &info->var)) {
			info->var.xres = info->var.xres_virtual = INIT_XRES;
			info->var.yres = info->var.yres_virtual = INIT_YRES;
			info->var.bits_per_pixel = INIT_BPP;
		}
	} else
#endif
	{
		info->var.xres = info->var.xres_virtual = INIT_XRES;
		info->var.yres = info->var.yres_virtual = INIT_YRES;
		info->var.bits_per_pixel = INIT_BPP;
	}

	if ((info->var.xres * info->var.yres) * (info->var.bits_per_pixel >> 3) > info->fix.smem_len
	    || !(compute_imstt_regvals(par, info->var.xres, info->var.yres))) {
		printk("imsttfb: %ux%ux%u not supported\n", info->var.xres, info->var.yres, info->var.bits_per_pixel);
		framebuffer_release(info);
		return;
	}

	sprintf(info->fix.id, "IMS TT (%s)", par->ramdac == IBM ? "IBM" : "TVP");
	info->fix.mmio_len = 0x1000;
	info->fix.accel = FB_ACCEL_IMS_TWINTURBO;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = info->var.bits_per_pixel == 8 ? FB_VISUAL_PSEUDOCOLOR
							: FB_VISUAL_DIRECTCOLOR;
	info->fix.line_length = info->var.xres * (info->var.bits_per_pixel >> 3);
	info->fix.xpanstep = 8;
	info->fix.ypanstep = 1;
	info->fix.ywrapstep = 0;

	info->var.accel_flags = FB_ACCELF_TEXT;

//	if (par->ramdac == IBM)
//		imstt_cursor_init(info);
	if (info->var.green.length == 6)
		set_565(par);
	else
		set_555(par);
	set_imstt_regvals(info, info->var.bits_per_pixel);

	info->var.pixclock = 1000000 / getclkMHz(par);

	info->fbops = &imsttfb_ops;
	info->flags = FBINFO_DEFAULT |
                      FBINFO_HWACCEL_COPYAREA |
	              FBINFO_HWACCEL_FILLRECT |
	              FBINFO_HWACCEL_YPAN;

	fb_alloc_cmap(&info->cmap, 0, 0);

	if (register_framebuffer(info) < 0) {
		framebuffer_release(info);
		return;
	}

	tmp = (read_reg_le32(par->dc_regs, SSTATUS) & 0x0f00) >> 8;
	fb_info(info, "%s frame buffer; %uMB vram; chip version %u\n",
		info->fix.id, info->fix.smem_len >> 20, tmp);
}