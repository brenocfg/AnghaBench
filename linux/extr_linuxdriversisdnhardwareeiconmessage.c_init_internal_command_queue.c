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
typedef  size_t word ;
struct TYPE_3__ {int /*<<< orphan*/ ** internal_command_queue; scalar_t__ internal_command; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 size_t MAX_INTERNAL_COMMAND_LEVELS ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char*,int) ; 

__attribute__((used)) static void init_internal_command_queue(PLCI *plci)
{
	word i;

	dbug(1, dprintf("%s,%d: init_internal_command_queue",
			(char *)(FILE_), __LINE__));

	plci->internal_command = 0;
	for (i = 0; i < MAX_INTERNAL_COMMAND_LEVELS; i++)
		plci->internal_command_queue[i] = NULL;
}