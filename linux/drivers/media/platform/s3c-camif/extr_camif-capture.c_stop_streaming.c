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
struct camif_vp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  camif_stop_capture (struct camif_vp*) ; 
 struct camif_vp* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *vq)
{
	struct camif_vp *vp = vb2_get_drv_priv(vq);
	camif_stop_capture(vp);
}