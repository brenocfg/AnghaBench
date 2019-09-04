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
struct qib_user_sdma_queue {int dummy; } ;
struct qib_user_sdma_pkt {scalar_t__ frag_size; scalar_t__ bytes_togo; int /*<<< orphan*/  addr; } ;
struct qib_devdata {int dummy; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int qib_user_sdma_coalesce (struct qib_devdata const*,struct qib_user_sdma_queue*,struct qib_user_sdma_pkt*,struct iovec const*,unsigned long) ; 
 int qib_user_sdma_pin_pkt (struct qib_devdata const*,struct qib_user_sdma_queue*,struct qib_user_sdma_pkt*,struct iovec const*,unsigned long) ; 

__attribute__((used)) static int qib_user_sdma_init_payload(const struct qib_devdata *dd,
				      struct qib_user_sdma_queue *pq,
				      struct qib_user_sdma_pkt *pkt,
				      const struct iovec *iov,
				      unsigned long niov, int npages)
{
	int ret = 0;

	if (pkt->frag_size == pkt->bytes_togo &&
			npages >= ARRAY_SIZE(pkt->addr))
		ret = qib_user_sdma_coalesce(dd, pq, pkt, iov, niov);
	else
		ret = qib_user_sdma_pin_pkt(dd, pq, pkt, iov, niov);

	return ret;
}