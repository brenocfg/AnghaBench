#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct nicvf {TYPE_1__* qs; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int rq_cnt; int sq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 int MAX_RCV_QUEUES_PER_QS ; 
 int nicvf_n_queue_stats ; 
 TYPE_2__* nicvf_queue_stats ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static void nicvf_get_qset_strings(struct nicvf *nic, u8 **data, int qset)
{
	int stats, qidx;
	int start_qidx = qset * MAX_RCV_QUEUES_PER_QS;

	for (qidx = 0; qidx < nic->qs->rq_cnt; qidx++) {
		for (stats = 0; stats < nicvf_n_queue_stats; stats++) {
			sprintf(*data, "rxq%d: %s", qidx + start_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		}
	}

	for (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) {
		for (stats = 0; stats < nicvf_n_queue_stats; stats++) {
			sprintf(*data, "txq%d: %s", qidx + start_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTRING_LEN;
		}
	}
}