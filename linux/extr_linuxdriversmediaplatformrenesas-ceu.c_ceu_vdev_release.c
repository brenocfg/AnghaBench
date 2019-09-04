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
struct video_device {int dummy; } ;
struct ceu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ceu_device*) ; 
 struct ceu_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void ceu_vdev_release(struct video_device *vdev)
{
	struct ceu_device *ceudev = video_get_drvdata(vdev);

	kfree(ceudev);
}