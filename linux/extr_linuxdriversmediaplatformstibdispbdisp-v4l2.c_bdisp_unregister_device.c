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
struct TYPE_2__ {int /*<<< orphan*/  vdev; scalar_t__ m2m_dev; } ;
struct bdisp_dev {TYPE_1__ m2m; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_release (scalar_t__) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdisp_unregister_device(struct bdisp_dev *bdisp)
{
	if (!bdisp)
		return;

	if (bdisp->m2m.m2m_dev)
		v4l2_m2m_release(bdisp->m2m.m2m_dev);

	video_unregister_device(bdisp->m2m.vdev);
}