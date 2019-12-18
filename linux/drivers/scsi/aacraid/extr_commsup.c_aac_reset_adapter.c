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
typedef  int /*<<< orphan*/  u8 ;
struct fib {int dummy; } ;
struct aac_pause {void* count; void* noRescan; void* min; void* timeout; void* type; void* command; } ;
struct aac_dev {int in_reset; struct Scsi_Host* scsi_host_ptr; int /*<<< orphan*/  fib_lock; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;

/* Variables and functions */
 int CT_PAUSE_IO ; 
 int /*<<< orphan*/  ContainerCommand ; 
 int EBUSY ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  FsaNormal ; 
 int VM_ContainerConfig ; 
 int _aac_reset_adapter (struct aac_dev*,int,int /*<<< orphan*/ ) ; 
 int aac_check_reset ; 
 struct fib* aac_fib_alloc (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aac_send_shutdown (struct aac_dev*) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ fib_data (struct fib*) ; 
 int /*<<< orphan*/  scsi_block_requests (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ spin_trylock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int aac_reset_adapter(struct aac_dev *aac, int forced, u8 reset_type)
{
	unsigned long flagv = 0;
	int retval;
	struct Scsi_Host * host;
	int bled;

	if (spin_trylock_irqsave(&aac->fib_lock, flagv) == 0)
		return -EBUSY;

	if (aac->in_reset) {
		spin_unlock_irqrestore(&aac->fib_lock, flagv);
		return -EBUSY;
	}
	aac->in_reset = 1;
	spin_unlock_irqrestore(&aac->fib_lock, flagv);

	/*
	 * Wait for all commands to complete to this specific
	 * target (block maximum 60 seconds). Although not necessary,
	 * it does make us a good storage citizen.
	 */
	host = aac->scsi_host_ptr;
	scsi_block_requests(host);

	/* Quiesce build, flush cache, write through mode */
	if (forced < 2)
		aac_send_shutdown(aac);
	spin_lock_irqsave(host->host_lock, flagv);
	bled = forced ? forced :
			(aac_check_reset != 0 && aac_check_reset != 1);
	retval = _aac_reset_adapter(aac, bled, reset_type);
	spin_unlock_irqrestore(host->host_lock, flagv);

	if ((forced < 2) && (retval == -ENODEV)) {
		/* Unwind aac_send_shutdown() IOP_RESET unsupported/disabled */
		struct fib * fibctx = aac_fib_alloc(aac);
		if (fibctx) {
			struct aac_pause *cmd;
			int status;

			aac_fib_init(fibctx);

			cmd = (struct aac_pause *) fib_data(fibctx);

			cmd->command = cpu_to_le32(VM_ContainerConfig);
			cmd->type = cpu_to_le32(CT_PAUSE_IO);
			cmd->timeout = cpu_to_le32(1);
			cmd->min = cpu_to_le32(1);
			cmd->noRescan = cpu_to_le32(1);
			cmd->count = cpu_to_le32(0);

			status = aac_fib_send(ContainerCommand,
			  fibctx,
			  sizeof(struct aac_pause),
			  FsaNormal,
			  -2 /* Timeout silently */, 1,
			  NULL, NULL);

			if (status >= 0)
				aac_fib_complete(fibctx);
			/* FIB should be freed only after getting
			 * the response from the F/W */
			if (status != -ERESTARTSYS)
				aac_fib_free(fibctx);
		}
	}

	return retval;
}