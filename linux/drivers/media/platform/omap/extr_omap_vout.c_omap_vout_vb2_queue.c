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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct omap_vout_device {int /*<<< orphan*/  dma_queue; } ;
struct omap_vout_buffer {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct omap_vout_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 struct omap_vout_buffer* vb2_to_omap_vout_buffer (struct vb2_buffer*) ; 

__attribute__((used)) static void omap_vout_vb2_queue(struct vb2_buffer *vb)
{
	struct omap_vout_device *vout = vb2_get_drv_priv(vb->vb2_queue);
	struct omap_vout_buffer *voutbuf = vb2_to_omap_vout_buffer(vb);

	list_add_tail(&voutbuf->queue, &vout->dma_queue);
}