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
struct TYPE_2__ {int /*<<< orphan*/ * md_capture_buff; int /*<<< orphan*/ * md_template; } ;
struct netxen_adapter {TYPE_1__ mdump; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void netxen_cleanup_minidump(struct netxen_adapter *adapter)
{
	kfree(adapter->mdump.md_template);
	adapter->mdump.md_template = NULL;

	if (adapter->mdump.md_capture_buff) {
		vfree(adapter->mdump.md_capture_buff);
		adapter->mdump.md_capture_buff = NULL;
	}
}