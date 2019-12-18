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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qbman_swp {TYPE_1__* desc; } ;
struct qbman_release_desc {unsigned int verb; int /*<<< orphan*/  bpid; int /*<<< orphan*/ * buf; } ;
struct TYPE_2__ {int qman_version; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_RCR (int) ; 
 int /*<<< orphan*/  QBMAN_CENA_SWP_RCR_MEM (int) ; 
 int /*<<< orphan*/  QBMAN_CINH_SWP_RAR ; 
 scalar_t__ QBMAN_CINH_SWP_RCR_AM_RT ; 
 int QMAN_REV_5000 ; 
 int QMAN_REV_MASK ; 
 int /*<<< orphan*/  QMAN_RT_MODE ; 
 int RAR_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAR_SUCCESS (int /*<<< orphan*/ ) ; 
 unsigned int RAR_VB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 struct qbman_release_desc* qbman_get_cmd (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_read_register (struct qbman_swp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_write_register (struct qbman_swp*,scalar_t__,int /*<<< orphan*/ ) ; 

int qbman_swp_release(struct qbman_swp *s, const struct qbman_release_desc *d,
		      const u64 *buffers, unsigned int num_buffers)
{
	int i;
	struct qbman_release_desc *p;
	u32 rar;

	if (!num_buffers || (num_buffers > 7))
		return -EINVAL;

	rar = qbman_read_register(s, QBMAN_CINH_SWP_RAR);
	if (!RAR_SUCCESS(rar))
		return -EBUSY;

	/* Start the release command */
	if ((s->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000)
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_RCR(RAR_IDX(rar)));
	else
		p = qbman_get_cmd(s, QBMAN_CENA_SWP_RCR_MEM(RAR_IDX(rar)));
	/* Copy the caller's buffer pointers to the command */
	for (i = 0; i < num_buffers; i++)
		p->buf[i] = cpu_to_le64(buffers[i]);
	p->bpid = d->bpid;

	if ((s->desc->qman_version & QMAN_REV_MASK) < QMAN_REV_5000) {
		/*
		 * Set the verb byte, have to substitute in the valid-bit
		 * and the number of buffers.
		 */
		dma_wmb();
		p->verb = d->verb | RAR_VB(rar) | num_buffers;
	} else {
		p->verb = d->verb | RAR_VB(rar) | num_buffers;
		dma_wmb();
		qbman_write_register(s, QBMAN_CINH_SWP_RCR_AM_RT +
				     RAR_IDX(rar)  * 4, QMAN_RT_MODE);
	}

	return 0;
}