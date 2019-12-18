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
struct stp_policy {TYPE_2__* stm; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* pdrv; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct stp_policy* to_stp_policy (struct config_item*) ; 

__attribute__((used)) static ssize_t stp_policy_protocol_show(struct config_item *item,
					char *page)
{
	struct stp_policy *policy = to_stp_policy(item);
	ssize_t count;

	count = sprintf(page, "%s\n",
			(policy && policy->stm) ?
			policy->stm->pdrv->name :
			"<none>");

	return count;
}