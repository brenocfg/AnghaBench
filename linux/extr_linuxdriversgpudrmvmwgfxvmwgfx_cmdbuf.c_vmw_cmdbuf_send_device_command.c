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
struct vmw_cmdbuf_man {int /*<<< orphan*/  lock; } ;
struct vmw_cmdbuf_header {int /*<<< orphan*/  cb_context; TYPE_1__* cb_header; } ;
struct TYPE_2__ {size_t length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SVGA_CB_CONTEXT_DEVICE ; 
 int SVGA_CB_STATUS_COMPLETED ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* vmw_cmdbuf_alloc (struct vmw_cmdbuf_man*,size_t,int,struct vmw_cmdbuf_header**) ; 
 int /*<<< orphan*/  vmw_cmdbuf_header_free (struct vmw_cmdbuf_header*) ; 
 int vmw_cmdbuf_header_submit (struct vmw_cmdbuf_header*) ; 

__attribute__((used)) static int vmw_cmdbuf_send_device_command(struct vmw_cmdbuf_man *man,
					  const void *command,
					  size_t size)
{
	struct vmw_cmdbuf_header *header;
	int status;
	void *cmd = vmw_cmdbuf_alloc(man, size, false, &header);

	if (IS_ERR(cmd))
		return PTR_ERR(cmd);

	memcpy(cmd, command, size);
	header->cb_header->length = size;
	header->cb_context = SVGA_CB_CONTEXT_DEVICE;
	spin_lock(&man->lock);
	status = vmw_cmdbuf_header_submit(header);
	spin_unlock(&man->lock);
	vmw_cmdbuf_header_free(header);

	if (status != SVGA_CB_STATUS_COMPLETED) {
		DRM_ERROR("Device context command failed with status %d\n",
			  status);
		return -EINVAL;
	}

	return 0;
}