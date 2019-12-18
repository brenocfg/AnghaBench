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
struct vb2_queue {int dummy; } ;
struct sta2x11_vip {int /*<<< orphan*/  active; int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVP_ITM ; 
 int DVP_IT_VSB ; 
 int DVP_IT_VST ; 
 int /*<<< orphan*/  reg_write (struct sta2x11_vip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_dma (struct sta2x11_vip*,int /*<<< orphan*/ ) ; 
 struct sta2x11_vip* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct sta2x11_vip *vip = vb2_get_drv_priv(vq);

	spin_lock_irq(&vip->slock);
	/* Enable interrupt VSYNC Top and Bottom*/
	reg_write(vip, DVP_ITM, DVP_IT_VSB | DVP_IT_VST);
	spin_unlock_irq(&vip->slock);

	if (count)
		start_dma(vip, vip->active);

	return 0;
}