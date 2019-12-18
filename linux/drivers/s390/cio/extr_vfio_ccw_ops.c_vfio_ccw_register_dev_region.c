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
typedef  int /*<<< orphan*/  u32 ;
struct vfio_ccw_regops {int dummy; } ;
struct vfio_ccw_region {unsigned int subtype; size_t size; void* data; int /*<<< orphan*/  flags; struct vfio_ccw_regops const* ops; int /*<<< orphan*/  type; } ;
struct vfio_ccw_private {int num_regions; struct vfio_ccw_region* region; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VFIO_REGION_TYPE_CCW ; 
 struct vfio_ccw_region* krealloc (struct vfio_ccw_region*,int,int /*<<< orphan*/ ) ; 

int vfio_ccw_register_dev_region(struct vfio_ccw_private *private,
				 unsigned int subtype,
				 const struct vfio_ccw_regops *ops,
				 size_t size, u32 flags, void *data)
{
	struct vfio_ccw_region *region;

	region = krealloc(private->region,
			  (private->num_regions + 1) * sizeof(*region),
			  GFP_KERNEL);
	if (!region)
		return -ENOMEM;

	private->region = region;
	private->region[private->num_regions].type = VFIO_REGION_TYPE_CCW;
	private->region[private->num_regions].subtype = subtype;
	private->region[private->num_regions].ops = ops;
	private->region[private->num_regions].size = size;
	private->region[private->num_regions].flags = flags;
	private->region[private->num_regions].data = data;

	private->num_regions++;

	return 0;
}