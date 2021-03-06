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
struct nvbios_init {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_exec_set (struct nvbios_init*,int) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void
init_resume(struct nvbios_init *init)
{
	trace("RESUME\n");
	init->offset += 1;
	init_exec_set(init, true);
}