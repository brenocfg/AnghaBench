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
struct spu_queue {int /*<<< orphan*/  qhandle; int /*<<< orphan*/  q; } ;
struct spu_qreg {unsigned long type; struct spu_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CWQ_NUM_ENTRIES ; 
 long EINVAL ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 unsigned long sun4v_ncs_qconf (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun4v_ncs_sethead_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long spu_queue_register_workfn(void *arg)
{
	struct spu_qreg *qr = arg;
	struct spu_queue *p = qr->queue;
	unsigned long q_type = qr->type;
	unsigned long hv_ret;

	hv_ret = sun4v_ncs_qconf(q_type, __pa(p->q),
				 CWQ_NUM_ENTRIES, &p->qhandle);
	if (!hv_ret)
		sun4v_ncs_sethead_marker(p->qhandle, 0);

	return hv_ret ? -EINVAL : 0;
}