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
struct iio_mount_matrix {int /*<<< orphan*/  rotation; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rotation; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int device_property_read_string_array (struct device*,char const*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__ iio_mount_idmatrix ; 
 int iio_setup_mount_idmatrix (struct device*,struct iio_mount_matrix*) ; 

int iio_read_mount_matrix(struct device *dev, const char *propname,
			  struct iio_mount_matrix *matrix)
{
	size_t len = ARRAY_SIZE(iio_mount_idmatrix.rotation);
	int err;

	err = device_property_read_string_array(dev, propname,
						matrix->rotation, len);
	if (err == len)
		return 0;

	if (err >= 0)
		/* Invalid number of matrix entries. */
		return -EINVAL;

	if (err != -EINVAL)
		/* Invalid matrix declaration format. */
		return err;

	/* Matrix was not declared at all: fallback to identity. */
	return iio_setup_mount_idmatrix(dev, matrix);
}