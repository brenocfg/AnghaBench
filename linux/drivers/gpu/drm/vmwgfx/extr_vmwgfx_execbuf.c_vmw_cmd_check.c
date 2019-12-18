#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vmw_sw_context {int /*<<< orphan*/  kernel; } ;
struct vmw_private {int capabilities; } ;
struct vmw_cmd_entry {int (* func ) (struct vmw_private*,struct vmw_sw_context*,TYPE_1__*) ;scalar_t__ gb_enable; scalar_t__ gb_disable; int /*<<< orphan*/  user_allow; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ size; } ;
typedef  TYPE_1__ SVGA3dCmdHeader ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ SVGA_3D_CMD_BASE ; 
 scalar_t__ SVGA_3D_CMD_MAX ; 
 int SVGA_CAP_GBOBJECTS ; 
 scalar_t__ SVGA_CMD_MAX ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*,scalar_t__,...) ; 
 int stub1 (struct vmw_private*,struct vmw_sw_context*,TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int vmw_cmd_check_not_3d (struct vmw_private*,struct vmw_sw_context*,void*,scalar_t__*) ; 
 struct vmw_cmd_entry* vmw_cmd_entries ; 

__attribute__((used)) static int vmw_cmd_check(struct vmw_private *dev_priv,
			 struct vmw_sw_context *sw_context, void *buf,
			 uint32_t *size)
{
	uint32_t cmd_id;
	uint32_t size_remaining = *size;
	SVGA3dCmdHeader *header = (SVGA3dCmdHeader *) buf;
	int ret;
	const struct vmw_cmd_entry *entry;
	bool gb = dev_priv->capabilities & SVGA_CAP_GBOBJECTS;

	cmd_id = ((uint32_t *)buf)[0];
	/* Handle any none 3D commands */
	if (unlikely(cmd_id < SVGA_CMD_MAX))
		return vmw_cmd_check_not_3d(dev_priv, sw_context, buf, size);


	cmd_id = header->id;
	*size = header->size + sizeof(SVGA3dCmdHeader);

	cmd_id -= SVGA_3D_CMD_BASE;
	if (unlikely(*size > size_remaining))
		goto out_invalid;

	if (unlikely(cmd_id >= SVGA_3D_CMD_MAX - SVGA_3D_CMD_BASE))
		goto out_invalid;

	entry = &vmw_cmd_entries[cmd_id];
	if (unlikely(!entry->func))
		goto out_invalid;

	if (unlikely(!entry->user_allow && !sw_context->kernel))
		goto out_privileged;

	if (unlikely(entry->gb_disable && gb))
		goto out_old;

	if (unlikely(entry->gb_enable && !gb))
		goto out_new;

	ret = entry->func(dev_priv, sw_context, header);
	if (unlikely(ret != 0)) {
		VMW_DEBUG_USER("SVGA3D command: %d failed with error %d\n",
			       cmd_id + SVGA_3D_CMD_BASE, ret);
		return ret;
	}

	return 0;
out_invalid:
	VMW_DEBUG_USER("Invalid SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
out_privileged:
	VMW_DEBUG_USER("Privileged SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	return -EPERM;
out_old:
	VMW_DEBUG_USER("Deprecated (disallowed) SVGA3D command: %d\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
out_new:
	VMW_DEBUG_USER("SVGA3D command: %d not supported by virtual device.\n",
		       cmd_id + SVGA_3D_CMD_BASE);
	return -EINVAL;
}