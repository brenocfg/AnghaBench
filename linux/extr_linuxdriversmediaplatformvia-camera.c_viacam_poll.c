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
struct via_camera {int /*<<< orphan*/  vb_queue; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 struct via_camera* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  videobuf_poll_stream (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t viacam_poll(struct file *filp, struct poll_table_struct *pt)
{
	struct via_camera *cam = video_drvdata(filp);

	return videobuf_poll_stream(filp, &cam->vb_queue, pt);
}