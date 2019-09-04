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
struct queue {int /*<<< orphan*/  offset; } ;
struct fs_dev {int dummy; } ;
struct FS_QENTRY {long p0; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  FS_DEBUG_QUEUE ; 
 long Q_EMPTY ; 
 int /*<<< orphan*/  Q_INCWRAP ; 
 int /*<<< orphan*/  Q_RP (int /*<<< orphan*/ ) ; 
 int STATUS_CODE (struct FS_QENTRY*) ; 
 void* bus_to_virt (long) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 long read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_return_queue (struct fs_dev *dev, struct queue *q)
{
	long rq;
	struct FS_QENTRY *qe;
	void *tc;
  
	while (!((rq = read_fs (dev, Q_RP(q->offset))) & Q_EMPTY)) {
		fs_dprintk (FS_DEBUG_QUEUE, "reaping return queue entry at %lx\n", rq); 
		qe = bus_to_virt (rq);
    
		fs_dprintk (FS_DEBUG_QUEUE, "queue entry: %08x %08x %08x %08x. (%d)\n", 
			    qe->cmd, qe->p0, qe->p1, qe->p2, STATUS_CODE (qe));

		switch (STATUS_CODE (qe)) {
		case 5:
			tc = bus_to_virt (qe->p0);
			fs_dprintk (FS_DEBUG_ALLOC, "Free tc: %p\n", tc);
			kfree (tc);
			break;
		}
    
		write_fs (dev, Q_RP(q->offset), Q_INCWRAP);
	}
}