#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int active; } ;
struct TYPE_9__ {int bus_no; int dev_no; TYPE_2__ state; } ;
struct controlvm_message_packet {TYPE_3__ device_change_state; } ;
struct TYPE_7__ {struct controlvm_message_packet cmd; } ;
struct parahotplug_request {int id; TYPE_1__ msg; } ;
struct TYPE_12__ {TYPE_5__* acpi_device; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_11__ {TYPE_4__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 TYPE_6__* chipset_dev ; 
 int kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int parahotplug_request_kickoff(struct parahotplug_request *req)
{
	struct controlvm_message_packet *cmd = &req->msg.cmd;
	char env_cmd[40], env_id[40], env_state[40], env_bus[40], env_dev[40],
	     env_func[40];
	char *envp[] = { env_cmd, env_id, env_state, env_bus, env_dev,
			 env_func, NULL
	};

	sprintf(env_cmd, "VISOR_PARAHOTPLUG=1");
	sprintf(env_id, "VISOR_PARAHOTPLUG_ID=%d", req->id);
	sprintf(env_state, "VISOR_PARAHOTPLUG_STATE=%d",
		cmd->device_change_state.state.active);
	sprintf(env_bus, "VISOR_PARAHOTPLUG_BUS=%d",
		cmd->device_change_state.bus_no);
	sprintf(env_dev, "VISOR_PARAHOTPLUG_DEVICE=%d",
		cmd->device_change_state.dev_no >> 3);
	sprintf(env_func, "VISOR_PARAHOTPLUG_FUNCTION=%d",
		cmd->device_change_state.dev_no & 0x7);
	return kobject_uevent_env(&chipset_dev->acpi_device->dev.kobj,
				  KOBJ_CHANGE, envp);
}