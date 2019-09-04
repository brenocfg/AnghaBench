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
 int /*<<< orphan*/  s3c_camif_unregister_video_node (struct camif_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void camif_unregister_video_nodes(struct camif_dev *camif)
{
	s3c_camif_unregister_video_node(camif, VP_CODEC);
	s3c_camif_unregister_video_node(camif, VP_PREVIEW);
}