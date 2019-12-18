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
struct proc_dir_entry {int dummy; } ;
struct nubus_board {int slot; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  proc_bus_nubus_dir ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

struct proc_dir_entry *nubus_proc_add_board(struct nubus_board *board)
{
	char name[2];

	if (!proc_bus_nubus_dir)
		return NULL;
	snprintf(name, sizeof(name), "%x", board->slot);
	return proc_mkdir(name, proc_bus_nubus_dir);
}