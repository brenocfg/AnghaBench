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
struct rmi_smb_xport {int /*<<< orphan*/  mappingtable_mutex; int /*<<< orphan*/  mapping_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rmi_smb_clear_state(struct rmi_smb_xport *rmi_smb)
{
	/* the mapping table has been flushed, discard the current one */
	mutex_lock(&rmi_smb->mappingtable_mutex);
	memset(rmi_smb->mapping_table, 0, sizeof(rmi_smb->mapping_table));
	mutex_unlock(&rmi_smb->mappingtable_mutex);
}