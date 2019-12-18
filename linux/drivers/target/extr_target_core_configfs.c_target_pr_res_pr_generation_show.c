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
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int pr_generation; } ;
struct TYPE_4__ {TYPE_1__ t10_pr; } ;

/* Variables and functions */
 TYPE_2__* pr_to_dev (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t target_pr_res_pr_generation_show(struct config_item *item,
		char *page)
{
	return sprintf(page, "0x%08x\n", pr_to_dev(item)->t10_pr.pr_generation);
}