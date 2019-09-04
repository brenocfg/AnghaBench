#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfe_line {int dummy; } ;
struct vfe_device {int stream_count; int /*<<< orphan*/  stream_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* bus_enable_wr_if ) (struct vfe_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct vfe_device*,int /*<<< orphan*/ ) ; 
 struct vfe_device* to_vfe (struct vfe_line*) ; 
 int /*<<< orphan*/  vfe_disable_output (struct vfe_line*) ; 
 int /*<<< orphan*/  vfe_put_output (struct vfe_line*) ; 

__attribute__((used)) static int vfe_disable(struct vfe_line *line)
{
	struct vfe_device *vfe = to_vfe(line);

	vfe_disable_output(line);

	vfe_put_output(line);

	mutex_lock(&vfe->stream_lock);

	if (vfe->stream_count == 1)
		vfe->ops->bus_enable_wr_if(vfe, 0);

	vfe->stream_count--;

	mutex_unlock(&vfe->stream_lock);

	return 0;
}