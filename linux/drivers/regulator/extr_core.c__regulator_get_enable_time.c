#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_3__* desc; TYPE_1__* constraints; } ;
struct TYPE_6__ {int enable_time; TYPE_2__* ops; } ;
struct TYPE_5__ {int (* enable_time ) (struct regulator_dev*) ;} ;
struct TYPE_4__ {int enable_time; } ;

/* Variables and functions */
 int stub1 (struct regulator_dev*) ; 

__attribute__((used)) static int _regulator_get_enable_time(struct regulator_dev *rdev)
{
	if (rdev->constraints && rdev->constraints->enable_time)
		return rdev->constraints->enable_time;
	if (rdev->desc->ops->enable_time)
		return rdev->desc->ops->enable_time(rdev);
	return rdev->desc->enable_time;
}