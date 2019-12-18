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
struct vfio_ccw_private {int /*<<< orphan*/  cmd_region; } ;
struct ccw_cmd_region {int dummy; } ;

/* Variables and functions */
 int VFIO_REGION_INFO_FLAG_READ ; 
 int VFIO_REGION_INFO_FLAG_WRITE ; 
 int /*<<< orphan*/  VFIO_REGION_SUBTYPE_CCW_ASYNC_CMD ; 
 int /*<<< orphan*/  vfio_ccw_async_region_ops ; 
 int vfio_ccw_register_dev_region (struct vfio_ccw_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

int vfio_ccw_register_async_dev_regions(struct vfio_ccw_private *private)
{
	return vfio_ccw_register_dev_region(private,
					    VFIO_REGION_SUBTYPE_CCW_ASYNC_CMD,
					    &vfio_ccw_async_region_ops,
					    sizeof(struct ccw_cmd_region),
					    VFIO_REGION_INFO_FLAG_READ |
					    VFIO_REGION_INFO_FLAG_WRITE,
					    private->cmd_region);
}