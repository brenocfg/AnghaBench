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
struct imgu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGU_NODE_NUM ; 
 int /*<<< orphan*/  imgu_v4l2_nodes_cleanup_pipe (struct imgu_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imgu_v4l2_subdev_cleanup (struct imgu_device*,int) ; 

__attribute__((used)) static void imgu_v4l2_cleanup_pipes(struct imgu_device *imgu, unsigned int pipe)
{
	int i;

	for (i = 0; i < pipe; i++) {
		imgu_v4l2_nodes_cleanup_pipe(imgu, i, IMGU_NODE_NUM);
		imgu_v4l2_subdev_cleanup(imgu, i);
	}
}