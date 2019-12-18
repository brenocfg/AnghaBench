#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int smem_len; int /*<<< orphan*/  smem_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmap; int /*<<< orphan*/  flags; int /*<<< orphan*/  pseudo_palette; scalar_t__ screen_base; TYPE_1__ fix; int /*<<< orphan*/  var; struct ocfb_dev* par; int /*<<< orphan*/ * device; int /*<<< orphan*/ * fbops; } ;
struct ocfb_dev {int /*<<< orphan*/  fb_phys; scalar_t__ fb_virt; TYPE_2__ info; scalar_t__ little_endian; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FBINFO_FOREIGN_ENDIAN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  PALETTE_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_mode ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ocfb_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_find_mode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mode_option ; 
 int /*<<< orphan*/  ocfb_init_fix (struct ocfb_dev*) ; 
 int /*<<< orphan*/  ocfb_init_var (struct ocfb_dev*) ; 
 int /*<<< orphan*/  ocfb_ops ; 
 int /*<<< orphan*/  ocfb_setupfb (struct ocfb_dev*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ocfb_dev*) ; 
 int register_framebuffer (TYPE_2__*) ; 

__attribute__((used)) static int ocfb_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct ocfb_dev *fbdev;
	struct resource *res;
	int fbsize;

	fbdev = devm_kzalloc(&pdev->dev, sizeof(*fbdev), GFP_KERNEL);
	if (!fbdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, fbdev);

	fbdev->info.fbops = &ocfb_ops;
	fbdev->info.device = &pdev->dev;
	fbdev->info.par = fbdev;

	/* Video mode setup */
	if (!fb_find_mode(&fbdev->info.var, &fbdev->info, mode_option,
			  NULL, 0, &default_mode, 16)) {
		dev_err(&pdev->dev, "No valid video modes found\n");
		return -EINVAL;
	}
	ocfb_init_var(fbdev);
	ocfb_init_fix(fbdev);

	/* Request I/O resource */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "I/O resource request failed\n");
		return -ENXIO;
	}
	fbdev->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(fbdev->regs))
		return PTR_ERR(fbdev->regs);

	/* Allocate framebuffer memory */
	fbsize = fbdev->info.fix.smem_len;
	fbdev->fb_virt = dma_alloc_coherent(&pdev->dev, PAGE_ALIGN(fbsize),
					    &fbdev->fb_phys, GFP_KERNEL);
	if (!fbdev->fb_virt) {
		dev_err(&pdev->dev,
			"Frame buffer memory allocation failed\n");
		return -ENOMEM;
	}
	fbdev->info.fix.smem_start = fbdev->fb_phys;
	fbdev->info.screen_base = fbdev->fb_virt;
	fbdev->info.pseudo_palette = fbdev->pseudo_palette;

	/* Clear framebuffer */
	memset_io(fbdev->fb_virt, 0, fbsize);

	/* Setup and enable the framebuffer */
	ocfb_setupfb(fbdev);

	if (fbdev->little_endian)
		fbdev->info.flags |= FBINFO_FOREIGN_ENDIAN;

	/* Allocate color map */
	ret = fb_alloc_cmap(&fbdev->info.cmap, PALETTE_SIZE, 0);
	if (ret) {
		dev_err(&pdev->dev, "Color map allocation failed\n");
		goto err_dma_free;
	}

	/* Register framebuffer */
	ret = register_framebuffer(&fbdev->info);
	if (ret) {
		dev_err(&pdev->dev, "Framebuffer registration failed\n");
		goto err_dealloc_cmap;
	}

	return 0;

err_dealloc_cmap:
	fb_dealloc_cmap(&fbdev->info.cmap);

err_dma_free:
	dma_free_coherent(&pdev->dev, PAGE_ALIGN(fbsize), fbdev->fb_virt,
			  fbdev->fb_phys);

	return ret;
}