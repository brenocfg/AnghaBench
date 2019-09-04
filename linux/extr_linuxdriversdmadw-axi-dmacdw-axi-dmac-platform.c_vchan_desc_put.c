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
struct virt_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axi_desc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vd_to_axi_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void vchan_desc_put(struct virt_dma_desc *vdesc)
{
	axi_desc_put(vd_to_axi_desc(vdesc));
}