#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; TYPE_1__ port_data; int /*<<< orphan*/  shim; } ;
struct intel_connector {TYPE_2__ hdcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_hdcp_cleanup(struct intel_connector *connector)
{
	if (!connector->hdcp.shim)
		return;

	mutex_lock(&connector->hdcp.mutex);
	kfree(connector->hdcp.port_data.streams);
	mutex_unlock(&connector->hdcp.mutex);
}