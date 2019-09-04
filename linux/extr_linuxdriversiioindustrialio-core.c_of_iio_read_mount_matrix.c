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
struct iio_mount_matrix {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int iio_setup_mount_idmatrix (struct device const*,struct iio_mount_matrix*) ; 

int of_iio_read_mount_matrix(const struct device *dev,
			     const char *propname,
			     struct iio_mount_matrix *matrix)
{
	return iio_setup_mount_idmatrix(dev, matrix);
}