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
struct rbd_device {int image_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int rbd_dev_v1_header_info (struct rbd_device*) ; 
 int rbd_dev_v2_header_info (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_image_format_valid (int) ; 

__attribute__((used)) static int rbd_dev_header_info(struct rbd_device *rbd_dev)
{
	rbd_assert(rbd_image_format_valid(rbd_dev->image_format));

	if (rbd_dev->image_format == 1)
		return rbd_dev_v1_header_info(rbd_dev);

	return rbd_dev_v2_header_info(rbd_dev);
}