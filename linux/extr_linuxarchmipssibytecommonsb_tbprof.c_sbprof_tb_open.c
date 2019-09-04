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
struct sbprof_tb {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ open; int /*<<< orphan*/  lock; int /*<<< orphan*/  tb_read; int /*<<< orphan*/  tb_sync; int /*<<< orphan*/  sbprof_tbbuf; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_TBSAMPLE_BYTES ; 
 scalar_t__ SB_CLOSED ; 
 scalar_t__ SB_OPEN ; 
 int /*<<< orphan*/  SB_OPENING ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ sbp ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 scalar_t__ xchg (scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbprof_tb_open(struct inode *inode, struct file *filp)
{
	int minor;

	minor = iminor(inode);
	if (minor != 0)
		return -ENODEV;

	if (xchg(&sbp.open, SB_OPENING) != SB_CLOSED)
		return -EBUSY;

	memset(&sbp, 0, sizeof(struct sbprof_tb));
	sbp.sbprof_tbbuf = vzalloc(MAX_TBSAMPLE_BYTES);
	if (!sbp.sbprof_tbbuf) {
		sbp.open = SB_CLOSED;
		wmb();
		return -ENOMEM;
	}

	init_waitqueue_head(&sbp.tb_sync);
	init_waitqueue_head(&sbp.tb_read);
	mutex_init(&sbp.lock);

	sbp.open = SB_OPEN;
	wmb();

	return 0;
}