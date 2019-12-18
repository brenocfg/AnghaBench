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
struct platform_device {int dummy; } ;
struct jpu {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  vfd_encoder; int /*<<< orphan*/  vfd_decoder; } ;

/* Variables and functions */
 struct jpu* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jpu_remove(struct platform_device *pdev)
{
	struct jpu *jpu = platform_get_drvdata(pdev);

	video_unregister_device(&jpu->vfd_decoder);
	video_unregister_device(&jpu->vfd_encoder);
	v4l2_m2m_release(jpu->m2m_dev);
	v4l2_device_unregister(&jpu->v4l2_dev);

	return 0;
}