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
 int /*<<< orphan*/  VP_CODEC ; 
 int /*<<< orphan*/  VP_PREVIEW ; 
 int s3c_camif_register_video_node (struct camif_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int camif_register_video_nodes(struct camif_dev *camif)
{
	int ret = s3c_camif_register_video_node(camif, VP_CODEC);
	if (ret < 0)
		return ret;

	return s3c_camif_register_video_node(camif, VP_PREVIEW);
}