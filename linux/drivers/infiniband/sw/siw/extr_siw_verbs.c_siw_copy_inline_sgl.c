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
struct siw_sqe {int num_sge; TYPE_1__* sge; } ;
struct ib_sge {scalar_t__ length; scalar_t__ addr; } ;
struct ib_send_wr {int num_sge; struct ib_sge* sg_list; } ;
struct TYPE_2__ {uintptr_t laddr; int length; scalar_t__ lkey; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIW_MAX_INLINE ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 

__attribute__((used)) static int siw_copy_inline_sgl(const struct ib_send_wr *core_wr,
			       struct siw_sqe *sqe)
{
	struct ib_sge *core_sge = core_wr->sg_list;
	void *kbuf = &sqe->sge[1];
	int num_sge = core_wr->num_sge, bytes = 0;

	sqe->sge[0].laddr = (uintptr_t)kbuf;
	sqe->sge[0].lkey = 0;

	while (num_sge--) {
		if (!core_sge->length) {
			core_sge++;
			continue;
		}
		bytes += core_sge->length;
		if (bytes > SIW_MAX_INLINE) {
			bytes = -EINVAL;
			break;
		}
		memcpy(kbuf, (void *)(uintptr_t)core_sge->addr,
		       core_sge->length);

		kbuf += core_sge->length;
		core_sge++;
	}
	sqe->sge[0].length = bytes > 0 ? bytes : 0;
	sqe->num_sge = bytes > 0 ? 1 : 0;

	return bytes;
}