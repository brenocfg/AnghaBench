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
 int IMGU_NODE_NUM ; 
 int imgu_v4l2_node_setup (struct imgu_device*,int,int) ; 
 int /*<<< orphan*/  imgu_v4l2_nodes_cleanup_pipe (struct imgu_device*,int,int) ; 

__attribute__((used)) static int imgu_v4l2_nodes_setup_pipe(struct imgu_device *imgu, int pipe)
{
	int i, r;

	for (i = 0; i < IMGU_NODE_NUM; i++) {
		r = imgu_v4l2_node_setup(imgu, pipe, i);
		if (r)
			goto cleanup;
	}

	return 0;

cleanup:
	imgu_v4l2_nodes_cleanup_pipe(imgu, pipe, i);
	return r;
}