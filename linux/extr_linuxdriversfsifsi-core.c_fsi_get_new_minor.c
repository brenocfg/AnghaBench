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
struct fsi_device {int /*<<< orphan*/  slave; } ;
typedef  enum fsi_dev_type { ____Placeholder_fsi_dev_type } fsi_dev_type ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int __fsi_get_new_minor (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

int fsi_get_new_minor(struct fsi_device *fdev, enum fsi_dev_type type,
		      dev_t *out_dev, int *out_index)
{
	return __fsi_get_new_minor(fdev->slave, type, out_dev, out_index);
}