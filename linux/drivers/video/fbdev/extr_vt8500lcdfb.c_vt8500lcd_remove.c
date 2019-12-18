#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__ cmap; } ;
struct vt8500lcd_info {int /*<<< orphan*/  regbase; int /*<<< orphan*/  palette_phys; int /*<<< orphan*/  palette_cpu; int /*<<< orphan*/  palette_size; TYPE_1__ fb; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_2__*) ; 
 int /*<<< orphan*/  free_irq (int,struct vt8500lcd_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct vt8500lcd_info* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vt8500lcd_remove(struct platform_device *pdev)
{
	struct vt8500lcd_info *fbi = platform_get_drvdata(pdev);
	struct resource *res;
	int irq;

	unregister_framebuffer(&fbi->fb);

	writel(0, fbi->regbase);

	if (fbi->fb.cmap.len)
		fb_dealloc_cmap(&fbi->fb.cmap);

	irq = platform_get_irq(pdev, 0);
	free_irq(irq, fbi);

	dma_free_coherent(&pdev->dev, fbi->palette_size,
			  fbi->palette_cpu, fbi->palette_phys);

	iounmap(fbi->regbase);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(res->start, resource_size(res));

	return 0;
}