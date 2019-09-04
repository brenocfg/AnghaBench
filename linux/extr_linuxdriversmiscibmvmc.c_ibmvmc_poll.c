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
struct ibmvmc_hmc {scalar_t__ queue_head; scalar_t__ queue_tail; } ;
struct ibmvmc_file_session {struct ibmvmc_hmc* hmc; } ;
struct file {struct ibmvmc_file_session* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int /*<<< orphan*/  ibmvmc_read_wait ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int ibmvmc_poll(struct file *file, poll_table *wait)
{
	struct ibmvmc_file_session *session;
	struct ibmvmc_hmc *hmc;
	unsigned int mask = 0;

	session = file->private_data;
	if (!session)
		return 0;

	hmc = session->hmc;
	if (!hmc)
		return 0;

	poll_wait(file, &ibmvmc_read_wait, wait);

	if (hmc->queue_head != hmc->queue_tail)
		mask |= POLLIN | POLLRDNORM;

	return mask;
}