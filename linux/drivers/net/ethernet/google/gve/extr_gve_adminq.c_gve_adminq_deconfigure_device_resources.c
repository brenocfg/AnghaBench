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
union gve_adminq_command {int /*<<< orphan*/  opcode; } ;
struct gve_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  GVE_ADMINQ_DECONFIGURE_DEVICE_RESOURCES ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int gve_adminq_execute_cmd (struct gve_priv*,union gve_adminq_command*) ; 
 int /*<<< orphan*/  memset (union gve_adminq_command*,int /*<<< orphan*/ ,int) ; 

int gve_adminq_deconfigure_device_resources(struct gve_priv *priv)
{
	union gve_adminq_command cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.opcode = cpu_to_be32(GVE_ADMINQ_DECONFIGURE_DEVICE_RESOURCES);

	return gve_adminq_execute_cmd(priv, &cmd);
}