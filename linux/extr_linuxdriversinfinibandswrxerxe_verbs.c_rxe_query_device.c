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
struct ib_device_attr {int dummy; } ;
struct rxe_dev {struct ib_device_attr attr; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

__attribute__((used)) static int rxe_query_device(struct ib_device *dev,
			    struct ib_device_attr *attr,
			    struct ib_udata *uhw)
{
	struct rxe_dev *rxe = to_rdev(dev);

	if (uhw->inlen || uhw->outlen)
		return -EINVAL;

	*attr = rxe->attr;
	return 0;
}