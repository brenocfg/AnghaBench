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
struct se_hba {int hba_flags; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int HBA_FLAGS_PSCSI_MODE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct se_hba* to_hba (struct config_item*) ; 

__attribute__((used)) static ssize_t target_hba_mode_show(struct config_item *item, char *page)
{
	struct se_hba *hba = to_hba(item);
	int hba_mode = 0;

	if (hba->hba_flags & HBA_FLAGS_PSCSI_MODE)
		hba_mode = 1;

	return sprintf(page, "%d\n", hba_mode);
}