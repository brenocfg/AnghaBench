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
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANCER_FW_DUMP_FILE ; 
 int be_cmd_status (int) ; 
 int lancer_cmd_delete_object (struct be_adapter*,int /*<<< orphan*/ ) ; 

int lancer_delete_dump(struct be_adapter *adapter)
{
	int status;

	status = lancer_cmd_delete_object(adapter, LANCER_FW_DUMP_FILE);
	return be_cmd_status(status);
}