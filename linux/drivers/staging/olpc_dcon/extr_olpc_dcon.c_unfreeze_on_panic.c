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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_dconload ) (int) ;} ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 TYPE_1__* pdata ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int unfreeze_on_panic(struct notifier_block *nb,
			     unsigned long e, void *p)
{
	pdata->set_dconload(1);
	return NOTIFY_DONE;
}