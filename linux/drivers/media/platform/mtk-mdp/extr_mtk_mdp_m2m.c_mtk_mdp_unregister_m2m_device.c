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
struct mtk_mdp_dev {int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

void mtk_mdp_unregister_m2m_device(struct mtk_mdp_dev *mdp)
{
	video_unregister_device(mdp->vdev);
	v4l2_m2m_release(mdp->m2m_dev);
}