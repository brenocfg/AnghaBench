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
struct qman_fq {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int NUM_ENQUEUES ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  fd_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ qman_enqueue (struct qman_fq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_enqueues(struct qman_fq *fq)
{
	unsigned int loop;
	int err = 0;

	for (loop = 0; loop < NUM_ENQUEUES; loop++) {
		if (qman_enqueue(fq, &fd)) {
			pr_crit("qman_enqueue() failed\n");
			err = -EIO;
		}
		fd_inc(&fd);
	}

	return err;
}