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
struct bttv {int /*<<< orphan*/  radio_dev; int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bttv_unregister_video(struct bttv *btv)
{
	video_unregister_device(&btv->video_dev);
	video_unregister_device(&btv->vbi_dev);
	video_unregister_device(&btv->radio_dev);
}