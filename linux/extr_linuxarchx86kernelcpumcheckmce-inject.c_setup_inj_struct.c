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
struct mce {int /*<<< orphan*/  cpuvendor; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_vendor; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  memset (struct mce*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_inj_struct(struct mce *m)
{
	memset(m, 0, sizeof(struct mce));

	m->cpuvendor = boot_cpu_data.x86_vendor;
}