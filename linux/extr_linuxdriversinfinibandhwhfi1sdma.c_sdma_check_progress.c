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
struct sdma_txreq {scalar_t__ num_desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  seqcount; } ;
struct sdma_engine {scalar_t__ desc_avail; TYPE_1__ head_lock; } ;
struct iowait {int (* sleep ) (struct sdma_engine*,struct iowait*,struct sdma_txreq*,unsigned int,int) ;} ;
typedef  int /*<<< orphan*/  seqcount_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 unsigned int raw_seqcount_begin (int /*<<< orphan*/  const*) ; 
 void* sdma_descq_freecnt (struct sdma_engine*) ; 
 int stub1 (struct sdma_engine*,struct iowait*,struct sdma_txreq*,unsigned int,int) ; 

__attribute__((used)) static int sdma_check_progress(
	struct sdma_engine *sde,
	struct iowait *wait,
	struct sdma_txreq *tx,
	bool pkts_sent)
{
	int ret;

	sde->desc_avail = sdma_descq_freecnt(sde);
	if (tx->num_desc <= sde->desc_avail)
		return -EAGAIN;
	/* pulse the head_lock */
	if (wait && wait->sleep) {
		unsigned seq;

		seq = raw_seqcount_begin(
			(const seqcount_t *)&sde->head_lock.seqcount);
		ret = wait->sleep(sde, wait, tx, seq, pkts_sent);
		if (ret == -EAGAIN)
			sde->desc_avail = sdma_descq_freecnt(sde);
	} else {
		ret = -EBUSY;
	}
	return ret;
}