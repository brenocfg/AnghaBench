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
struct se_hba {int hba_id; TYPE_2__* backend; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 char* TARGET_CORE_VERSION ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*,char*) ; 
 struct se_hba* to_hba (struct config_item*) ; 

__attribute__((used)) static ssize_t target_hba_info_show(struct config_item *item, char *page)
{
	struct se_hba *hba = to_hba(item);

	return sprintf(page, "HBA Index: %d plugin: %s version: %s\n",
			hba->hba_id, hba->backend->ops->name,
			TARGET_CORE_VERSION);
}