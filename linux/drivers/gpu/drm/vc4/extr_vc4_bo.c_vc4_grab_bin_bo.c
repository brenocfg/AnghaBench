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
struct vc4_file {scalar_t__ bin_bo_used; } ;
struct vc4_dev {int /*<<< orphan*/  v3d; } ;

/* Variables and functions */
 int ENODEV ; 
 int vc4_v3d_bin_bo_get (struct vc4_dev*,scalar_t__*) ; 

__attribute__((used)) static int vc4_grab_bin_bo(struct vc4_dev *vc4, struct vc4_file *vc4file)
{
	int ret;

	if (!vc4->v3d)
		return -ENODEV;

	if (vc4file->bin_bo_used)
		return 0;

	ret = vc4_v3d_bin_bo_get(vc4, &vc4file->bin_bo_used);
	if (ret)
		return ret;

	return 0;
}