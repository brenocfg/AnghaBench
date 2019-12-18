#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vip_buffer {scalar_t__ dma; } ;
struct TYPE_2__ {scalar_t__ field; int width; } ;
struct sta2x11_vip {int /*<<< orphan*/  slock; TYPE_1__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVP_CTL ; 
 int DVP_CTL_ENA ; 
 int /*<<< orphan*/  DVP_VBP ; 
 int /*<<< orphan*/  DVP_VTP ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 int reg_read (struct sta2x11_vip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct sta2x11_vip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void start_dma(struct sta2x11_vip *vip, struct vip_buffer *vip_buf)
{
	unsigned long offset = 0;

	if (vip->format.field == V4L2_FIELD_INTERLACED)
		offset = vip->format.width * 2;

	spin_lock_irq(&vip->slock);
	/* Enable acquisition */
	reg_write(vip, DVP_CTL, reg_read(vip, DVP_CTL) | DVP_CTL_ENA);
	/* Set Top and Bottom Field memory address */
	reg_write(vip, DVP_VTP, (u32)vip_buf->dma);
	reg_write(vip, DVP_VBP, (u32)vip_buf->dma + offset);
	spin_unlock_irq(&vip->slock);
}