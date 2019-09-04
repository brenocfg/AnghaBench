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
struct delta_dev {int /*<<< orphan*/  vdev; scalar_t__ m2m_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_release (scalar_t__) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delta_unregister_device(struct delta_dev *delta)
{
	if (!delta)
		return;

	if (delta->m2m_dev)
		v4l2_m2m_release(delta->m2m_dev);

	video_unregister_device(delta->vdev);
}