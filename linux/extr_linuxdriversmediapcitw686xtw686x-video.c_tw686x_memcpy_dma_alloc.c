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
typedef  int /*<<< orphan*/  u32 ;
struct tw686x_video_channel {size_t ch; int width; int height; TYPE_2__* dma_descs; TYPE_1__* format; struct tw686x_dev* dev; } ;
struct tw686x_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  pci_dev; } ;
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/  phys; void* virt; } ;
struct TYPE_3__ {int depth; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * VDMA_B_ADDR ; 
 int /*<<< orphan*/ * VDMA_P_ADDR ; 
 int /*<<< orphan*/  WARN (void*,char*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reg_write (struct tw686x_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,size_t,char*) ; 

__attribute__((used)) static int tw686x_memcpy_dma_alloc(struct tw686x_video_channel *vc,
				   unsigned int pb)
{
	struct tw686x_dev *dev = vc->dev;
	u32 reg = pb ? VDMA_B_ADDR[vc->ch] : VDMA_P_ADDR[vc->ch];
	unsigned int len;
	void *virt;

	WARN(vc->dma_descs[pb].virt,
	     "Allocating buffer but previous still here\n");

	len = (vc->width * vc->height * vc->format->depth) >> 3;
	virt = pci_alloc_consistent(dev->pci_dev, len,
				    &vc->dma_descs[pb].phys);
	if (!virt) {
		v4l2_err(&dev->v4l2_dev,
			 "dma%d: unable to allocate %s-buffer\n",
			 vc->ch, pb ? "B" : "P");
		return -ENOMEM;
	}
	vc->dma_descs[pb].size = len;
	vc->dma_descs[pb].virt = virt;
	reg_write(dev, reg, vc->dma_descs[pb].phys);

	return 0;
}