#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ owner; scalar_t__ is_owned; } ;
struct gasket_cdev_info {TYPE_1__ ownership; } ;
struct TYPE_4__ {scalar_t__ tgid; } ;

/* Variables and functions */
 TYPE_2__* current ; 

__attribute__((used)) static int gasket_owned_by_current_tgid(struct gasket_cdev_info *info)
{
	return (info->ownership.is_owned &&
		(info->ownership.owner == current->tgid));
}