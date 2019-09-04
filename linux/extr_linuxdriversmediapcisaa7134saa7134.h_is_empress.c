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
struct video_device {int /*<<< orphan*/ * queue; } ;
struct saa7134_dev {int /*<<< orphan*/  empress_vbq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct video_device* video_devdata (struct file*) ; 
 struct saa7134_dev* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static inline bool is_empress(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct saa7134_dev *dev = video_get_drvdata(vdev);

	return vdev->queue == &dev->empress_vbq;
}