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
typedef  int /*<<< orphan*/  uuid_le ;
struct mei_cl_device {int /*<<< orphan*/  me_cl; } ;

/* Variables and functions */
 int /*<<< orphan*/  const* mei_me_cl_uuid (int /*<<< orphan*/ ) ; 

const uuid_le *mei_cldev_uuid(const struct mei_cl_device *cldev)
{
	return mei_me_cl_uuid(cldev->me_cl);
}