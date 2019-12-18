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
struct hw_fib {int dummy; } ;
struct fib {TYPE_2__* hw_fib_va; struct aac_dev* dev; } ;
struct aac_fibhdr {int dummy; } ;
struct aac_dev {scalar_t__ sa_firmware; } ;
struct aac_aifcmd {int command; } ;
typedef  int /*<<< orphan*/  fib_callback ;
struct TYPE_3__ {int XferState; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  AifReqEvent ; 
 int /*<<< orphan*/  AifRequest ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsaNormal ; 
 int /*<<< orphan*/  NoMoreAifDataAvailable ; 
 int /*<<< orphan*/  aac_fib_complete (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_free (struct fib*) ; 
 int /*<<< orphan*/  aac_fib_init (struct fib*) ; 
 int aac_fib_send (int /*<<< orphan*/ ,struct fib*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fib*) ; 
 int /*<<< orphan*/  aac_intr_normal (struct aac_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ fib_data (struct fib*) ; 

__attribute__((used)) static void aac_aif_callback(void *context, struct fib * fibptr)
{
	struct fib *fibctx;
	struct aac_dev *dev;
	struct aac_aifcmd *cmd;
	int status;

	fibctx = (struct fib *)context;
	BUG_ON(fibptr == NULL);
	dev = fibptr->dev;

	if ((fibptr->hw_fib_va->header.XferState &
	    cpu_to_le32(NoMoreAifDataAvailable)) ||
		dev->sa_firmware) {
		aac_fib_complete(fibptr);
		aac_fib_free(fibptr);
		return;
	}

	aac_intr_normal(dev, 0, 1, 0, fibptr->hw_fib_va);

	aac_fib_init(fibctx);
	cmd = (struct aac_aifcmd *) fib_data(fibctx);
	cmd->command = cpu_to_le32(AifReqEvent);

	status = aac_fib_send(AifRequest,
		fibctx,
		sizeof(struct hw_fib)-sizeof(struct aac_fibhdr),
		FsaNormal,
		0, 1,
		(fib_callback)aac_aif_callback, fibctx);
}