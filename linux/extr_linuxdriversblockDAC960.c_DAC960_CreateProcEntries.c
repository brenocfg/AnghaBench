#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_5__ {char* ControllerName; int ControllerNumber; struct proc_dir_entry* ControllerProcEntry; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/ * DAC960_ProcDirectoryEntry ; 
 int /*<<< orphan*/  dac960_current_status_proc_show ; 
 int /*<<< orphan*/  dac960_initial_status_proc_show ; 
 int /*<<< orphan*/  dac960_proc_show ; 
 int /*<<< orphan*/  dac960_user_command_proc_fops ; 
 int /*<<< orphan*/  proc_create_data (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  proc_create_single (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int /*<<< orphan*/ ,struct proc_dir_entry*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* proc_mkdir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void DAC960_CreateProcEntries(DAC960_Controller_T *Controller)
{
	struct proc_dir_entry *ControllerProcEntry;

	if (DAC960_ProcDirectoryEntry == NULL) {
		DAC960_ProcDirectoryEntry = proc_mkdir("rd", NULL);
		proc_create_single("status", 0, DAC960_ProcDirectoryEntry,
				dac960_proc_show);
	}

	snprintf(Controller->ControllerName, sizeof(Controller->ControllerName),
		 "c%d", Controller->ControllerNumber);
	ControllerProcEntry = proc_mkdir(Controller->ControllerName,
					 DAC960_ProcDirectoryEntry);
	proc_create_single_data("initial_status", 0, ControllerProcEntry,
			dac960_initial_status_proc_show, Controller);
	proc_create_single_data("current_status", 0, ControllerProcEntry,
			dac960_current_status_proc_show, Controller);
	proc_create_data("user_command", 0600, ControllerProcEntry, &dac960_user_command_proc_fops, Controller);
	Controller->ControllerProcEntry = ControllerProcEntry;
}