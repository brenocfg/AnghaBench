#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ControllerName; int /*<<< orphan*/ * ControllerProcEntry; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/ * DAC960_ProcDirectoryEntry ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DAC960_DestroyProcEntries(DAC960_Controller_T *Controller)
{
      if (Controller->ControllerProcEntry == NULL)
	      return;
      remove_proc_entry("initial_status", Controller->ControllerProcEntry);
      remove_proc_entry("current_status", Controller->ControllerProcEntry);
      remove_proc_entry("user_command", Controller->ControllerProcEntry);
      remove_proc_entry(Controller->ControllerName, DAC960_ProcDirectoryEntry);
      Controller->ControllerProcEntry = NULL;
}