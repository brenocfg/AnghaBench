#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  sysbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_9XX_CHIP_RESET ; 
 int /*<<< orphan*/  SYS_CHIP_RESET ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 int /*<<< orphan*/  cpu_wait () ; 
 TYPE_1__* nlm_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nlm_linux_exit(void)
{
	uint64_t sysbase = nlm_get_node(0)->sysbase;

	if (cpu_is_xlp9xx())
		nlm_write_sys_reg(sysbase, SYS_9XX_CHIP_RESET, 1);
	else
		nlm_write_sys_reg(sysbase, SYS_CHIP_RESET, 1);
	for ( ; ; )
		cpu_wait();
}