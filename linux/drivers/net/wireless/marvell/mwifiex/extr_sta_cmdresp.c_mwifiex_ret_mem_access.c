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
struct TYPE_4__ {void* value; void* addr; } ;
struct mwifiex_private {TYPE_2__ mem_rw; } ;
struct host_cmd_ds_mem_access {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mwifiex_ret_mem_access(struct mwifiex_private *priv,
		       struct host_cmd_ds_command *resp, void *pioctl_buf)
{
	struct host_cmd_ds_mem_access *mem = (void *)&resp->params.mem;

	priv->mem_rw.addr = le32_to_cpu(mem->addr);
	priv->mem_rw.value = le32_to_cpu(mem->value);

	return 0;
}