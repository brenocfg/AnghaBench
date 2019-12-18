#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;
struct au1100fb_regs {int dummy; } ;
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_10__ {int bits_per_pixel; int xres; int xres_virtual; int yres; int yres_virtual; } ;
struct TYPE_11__ {int smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  mmio_start; int /*<<< orphan*/  mmio_len; } ;
struct TYPE_8__ {TYPE_3__ cmap; TYPE_5__ var; int /*<<< orphan*/  pseudo_palette; TYPE_6__ fix; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  screen_base; } ;
struct au1100fb_device {int regs_len; int fb_len; TYPE_2__ info; struct clk* lcdclk; int /*<<< orphan*/  fb_mem; TYPE_1__* panel; int /*<<< orphan*/  fb_phys; int /*<<< orphan*/  regs_phys; struct au1100fb_regs* regs; int /*<<< orphan*/ * dev; } ;
struct TYPE_7__ {int xres; int yres; int bpp; } ;

/* Variables and functions */
 int AU1100FB_NBR_VIDEO_BUFFERS ; 
 int /*<<< orphan*/  AU1100_LCD_NBR_PALETTE_ENTRIES ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 scalar_t__ KSEG1ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 TYPE_6__ au1100fb_fix ; 
 int /*<<< orphan*/  au1100fb_ops ; 
 int /*<<< orphan*/  au1100fb_setmode (struct au1100fb_device*) ; 
 scalar_t__ au1100fb_setup (struct au1100fb_device*) ; 
 TYPE_5__ au1100fb_var ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct au1100fb_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fb_alloc_cmap (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_3__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,void*) ; 
 int /*<<< orphan*/  print_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  print_err (char*,...) ; 
 scalar_t__ register_framebuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int au1100fb_drv_probe(struct platform_device *dev)
{
	struct au1100fb_device *fbdev;
	struct resource *regs_res;
	struct clk *c;

	/* Allocate new device private */
	fbdev = devm_kzalloc(&dev->dev, sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		return -ENOMEM;

	if (au1100fb_setup(fbdev))
		goto failed;

	platform_set_drvdata(dev, (void *)fbdev);
	fbdev->dev = &dev->dev;

	/* Allocate region for our registers and map them */
	regs_res = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!regs_res) {
		print_err("fail to retrieve registers resource");
		return -EFAULT;
	}

	au1100fb_fix.mmio_start = regs_res->start;
	au1100fb_fix.mmio_len = resource_size(regs_res);

	if (!devm_request_mem_region(&dev->dev,
				     au1100fb_fix.mmio_start,
				     au1100fb_fix.mmio_len,
				     DRIVER_NAME)) {
		print_err("fail to lock memory region at 0x%08lx",
				au1100fb_fix.mmio_start);
		return -EBUSY;
	}

	fbdev->regs = (struct au1100fb_regs*)KSEG1ADDR(au1100fb_fix.mmio_start);

	print_dbg("Register memory map at %p", fbdev->regs);
	print_dbg("phys=0x%08x, size=%d", fbdev->regs_phys, fbdev->regs_len);

	c = clk_get(NULL, "lcd_intclk");
	if (!IS_ERR(c)) {
		fbdev->lcdclk = c;
		clk_set_rate(c, 48000000);
		clk_prepare_enable(c);
	}

	/* Allocate the framebuffer to the maximum screen size * nbr of video buffers */
	fbdev->fb_len = fbdev->panel->xres * fbdev->panel->yres *
		  	(fbdev->panel->bpp >> 3) * AU1100FB_NBR_VIDEO_BUFFERS;

	fbdev->fb_mem = dmam_alloc_coherent(&dev->dev,
					    PAGE_ALIGN(fbdev->fb_len),
					    &fbdev->fb_phys, GFP_KERNEL);
	if (!fbdev->fb_mem) {
		print_err("fail to allocate framebuffer (size: %dK))",
			  fbdev->fb_len / 1024);
		return -ENOMEM;
	}

	au1100fb_fix.smem_start = fbdev->fb_phys;
	au1100fb_fix.smem_len = fbdev->fb_len;

	print_dbg("Framebuffer memory map at %p", fbdev->fb_mem);
	print_dbg("phys=0x%08x, size=%dK", fbdev->fb_phys, fbdev->fb_len / 1024);

	/* load the panel info into the var struct */
	au1100fb_var.bits_per_pixel = fbdev->panel->bpp;
	au1100fb_var.xres = fbdev->panel->xres;
	au1100fb_var.xres_virtual = au1100fb_var.xres;
	au1100fb_var.yres = fbdev->panel->yres;
	au1100fb_var.yres_virtual = au1100fb_var.yres;

	fbdev->info.screen_base = fbdev->fb_mem;
	fbdev->info.fbops = &au1100fb_ops;
	fbdev->info.fix = au1100fb_fix;

	fbdev->info.pseudo_palette =
		devm_kcalloc(&dev->dev, 16, sizeof(u32), GFP_KERNEL);
	if (!fbdev->info.pseudo_palette)
		return -ENOMEM;

	if (fb_alloc_cmap(&fbdev->info.cmap, AU1100_LCD_NBR_PALETTE_ENTRIES, 0) < 0) {
		print_err("Fail to allocate colormap (%d entries)",
			   AU1100_LCD_NBR_PALETTE_ENTRIES);
		return -EFAULT;
	}

	fbdev->info.var = au1100fb_var;

	/* Set h/w registers */
	au1100fb_setmode(fbdev);

	/* Register new framebuffer */
	if (register_framebuffer(&fbdev->info) < 0) {
		print_err("cannot register new framebuffer");
		goto failed;
	}

	return 0;

failed:
	if (fbdev->lcdclk) {
		clk_disable_unprepare(fbdev->lcdclk);
		clk_put(fbdev->lcdclk);
	}
	if (fbdev->info.cmap.len != 0) {
		fb_dealloc_cmap(&fbdev->info.cmap);
	}

	return -ENODEV;
}