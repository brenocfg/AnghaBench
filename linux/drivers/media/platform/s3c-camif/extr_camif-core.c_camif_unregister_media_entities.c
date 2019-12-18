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
struct camif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  camif_unregister_sensor (struct camif_dev*) ; 
 int /*<<< orphan*/  camif_unregister_video_nodes (struct camif_dev*) ; 
 int /*<<< orphan*/  s3c_camif_unregister_subdev (struct camif_dev*) ; 

__attribute__((used)) static void camif_unregister_media_entities(struct camif_dev *camif)
{
	camif_unregister_video_nodes(camif);
	camif_unregister_sensor(camif);
	s3c_camif_unregister_subdev(camif);
}