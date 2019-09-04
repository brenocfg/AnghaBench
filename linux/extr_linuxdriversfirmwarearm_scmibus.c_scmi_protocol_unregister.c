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
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  protocol_lock ; 
 int /*<<< orphan*/  scmi_protocols ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void scmi_protocol_unregister(int protocol_id)
{
	spin_lock(&protocol_lock);
	idr_remove(&scmi_protocols, protocol_id);
	spin_unlock(&protocol_lock);
}