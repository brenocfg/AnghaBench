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
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_1__ iwpm_admin ; 

int iwpm_get_nlmsg_seq(void)
{
	return atomic_inc_return(&iwpm_admin.nlmsg_seq);
}