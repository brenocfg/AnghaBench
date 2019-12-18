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
struct fib {int dummy; } ;
struct aac_dev {int adapter_shutdown; scalar_t__ msi_enabled; int /*<<< orphan*/  ioctl_mutex; } ;
struct aac_close {void* cid; void* command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ContainerCommand ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int VM_CloseAll ; 
 scalar_t__ aac_adapter_check_health (struct aac_dev*) ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ aac_is_src (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_set_intx_mode (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_wait_for_io_completion (struct aac_dev*) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int aac_send_shutdown(struct aac_dev * dev)
{
	struct fib * fibctx;
	struct aac_close *cmd;
	int status = 0;

	if (aac_adapter_check_health(dev))
		return status;

	if (!dev->adapter_shutdown) {
		mutex_lock(&dev->ioctl_mutex);
		dev->adapter_shutdown = 1;
		mutex_unlock(&dev->ioctl_mutex);
	}

	aac_wait_for_io_completion(dev);

	fibctx = aac_fib_alloc(dev);
	if (!fibctx)
		return -ENOMEM;
	aac_fib_init(fibctx);

	cmd = (struct aac_close *) fib_data(fibctx);
	cmd->command = cpu_to_le32(VM_CloseAll);
	cmd->cid = cpu_to_le32(0xfffffffe);

	status = aac_fib_send(ContainerCommand,
			  fibctx,
			  sizeof(struct aac_close),
			  FsaNormal,
			  -2 /* Timeout silently */, 1,
			  NULL, NULL);

	if (status >= 0)
		aac_fib_complete(fibctx);
	/* FIB should be freed only after getting the response from the F/W */
	if (status != -ERESTARTSYS)
		aac_fib_free(fibctx);
	if (aac_is_src(dev) &&
	     dev->msi_enabled)
		aac_set_intx_mode(dev);
	return status;
}