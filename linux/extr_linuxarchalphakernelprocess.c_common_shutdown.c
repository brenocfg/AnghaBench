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
struct halt_info {int mode; char* restart_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  common_shutdown_1 ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct halt_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
common_shutdown(int mode, char *restart_cmd)
{
	struct halt_info args;
	args.mode = mode;
	args.restart_cmd = restart_cmd;
	on_each_cpu(common_shutdown_1, &args, 0);
}