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
struct snic_trc_data {int dummy; } ;
struct snic_trc {int max_idx; int enable; scalar_t__ wr_idx; scalar_t__ rd_idx; int /*<<< orphan*/  lock; struct snic_trc_data* buf; } ;
struct TYPE_2__ {struct snic_trc trc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  SNIC_ERR (char*,...) ; 
 int /*<<< orphan*/  SNIC_INFO (char*,int) ; 
 int SNIC_TRC_ENTRY_SZ ; 
 TYPE_1__* snic_glob ; 
 int snic_trace_max_pages ; 
 int /*<<< orphan*/  snic_trc_debugfs_init () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* vzalloc (int) ; 

int
snic_trc_init(void)
{
	struct snic_trc *trc = &snic_glob->trc;
	void *tbuf = NULL;
	int tbuf_sz = 0, ret;

	tbuf_sz = (snic_trace_max_pages * PAGE_SIZE);
	tbuf = vzalloc(tbuf_sz);
	if (!tbuf) {
		SNIC_ERR("Failed to Allocate Trace Buffer Size. %d\n", tbuf_sz);
		SNIC_ERR("Trace Facility not enabled.\n");
		ret = -ENOMEM;

		return ret;
	}

	trc->buf = (struct snic_trc_data *) tbuf;
	spin_lock_init(&trc->lock);

	snic_trc_debugfs_init();

	trc->max_idx = (tbuf_sz / SNIC_TRC_ENTRY_SZ);
	trc->rd_idx = trc->wr_idx = 0;
	trc->enable = true;
	SNIC_INFO("Trace Facility Enabled.\n Trace Buffer SZ %lu Pages.\n",
		  tbuf_sz / PAGE_SIZE);
	ret = 0;

	return ret;
}