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
struct saa7134_go7007 {int /*<<< orphan*/  sd; scalar_t__ bottom; scalar_t__ top; } ;
struct saa7134_dev {int /*<<< orphan*/ * empress_dev; } ;
struct go7007 {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vdev; int /*<<< orphan*/  status; struct saa7134_go7007* hpi_context; scalar_t__ audio_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  go7007_snd_remove (struct go7007*) ; 
 int /*<<< orphan*/  kfree (struct saa7134_go7007*) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 
 struct go7007* video_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int saa7134_go7007_fini(struct saa7134_dev *dev)
{
	struct go7007 *go;
	struct saa7134_go7007 *saa;

	if (NULL == dev->empress_dev)
		return 0;

	go = video_get_drvdata(dev->empress_dev);
	if (go->audio_enabled)
		go7007_snd_remove(go);

	saa = go->hpi_context;
	go->status = STATUS_SHUTDOWN;
	free_page((unsigned long)saa->top);
	free_page((unsigned long)saa->bottom);
	v4l2_device_unregister_subdev(&saa->sd);
	kfree(saa);
	video_unregister_device(&go->vdev);

	v4l2_device_put(&go->v4l2_dev);
	dev->empress_dev = NULL;

	return 0;
}