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
typedef  scalar_t__ u32 ;
struct host1x_firewall {scalar_t__ class; TYPE_1__* job; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_valid_class ) (scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static int check_class(struct host1x_firewall *fw, u32 class)
{
	if (!fw->job->is_valid_class) {
		if (fw->class != class)
			return -EINVAL;
	} else {
		if (!fw->job->is_valid_class(fw->class))
			return -EINVAL;
	}

	return 0;
}