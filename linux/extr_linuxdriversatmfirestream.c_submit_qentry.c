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
typedef  int u32 ;
struct queue {int /*<<< orphan*/  offset; } ;
struct fs_dev {int dummy; } ;
struct FS_QENTRY {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DEBUG_TXQ ; 
 int Q_FULL ; 
 int /*<<< orphan*/  Q_INCWRAP ; 
 int /*<<< orphan*/  Q_RP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_WP (int /*<<< orphan*/ ) ; 
 struct FS_QENTRY* bus_to_virt (int) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void submit_qentry (struct fs_dev *dev, struct queue *q, struct FS_QENTRY *qe)
{
	u32 wp;
	struct FS_QENTRY *cqe;

	/* XXX Sanity check: the write pointer can be checked to be 
	   still the same as the value passed as qe... -- REW */
	/*  udelay (5); */
	while ((wp = read_fs (dev, Q_WP (q->offset))) & Q_FULL) {
		fs_dprintk (FS_DEBUG_TXQ, "Found queue at %x full. Waiting.\n", 
			    q->offset);
		schedule ();
	}

	wp &= ~0xf;
	cqe = bus_to_virt (wp);
	if (qe != cqe) {
		fs_dprintk (FS_DEBUG_TXQ, "q mismatch! %p %p\n", qe, cqe);
	}

	write_fs (dev, Q_WP(q->offset), Q_INCWRAP);

	{
		static int c;
		if (!(c++ % 100))
			{
				int rp, wp;
				rp =  read_fs (dev, Q_RP(q->offset));
				wp =  read_fs (dev, Q_WP(q->offset));
				fs_dprintk (FS_DEBUG_TXQ, "q at %d: %x-%x: %x entries.\n", 
					    q->offset, rp, wp, wp-rp);
			}
	}
}