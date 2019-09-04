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

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pkt_debugfs_root ; 

__attribute__((used)) static void pkt_debugfs_cleanup(void)
{
	debugfs_remove(pkt_debugfs_root);
	pkt_debugfs_root = NULL;
}