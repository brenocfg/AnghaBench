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
struct snic_trc_data {scalar_t__ ts; } ;
struct snic_trc {size_t rd_idx; size_t wr_idx; size_t max_idx; int /*<<< orphan*/  lock; struct snic_trc_data* buf; } ;
struct TYPE_2__ {struct snic_trc trc; } ;

/* Variables and functions */
 int snic_fmt_trc_data (struct snic_trc_data*,char*,int) ; 
 TYPE_1__* snic_glob ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snic_get_trc_data(char *buf, int buf_sz)
{
	struct snic_trc_data *td = NULL;
	struct snic_trc *trc = &snic_glob->trc;
	unsigned long flags;

	spin_lock_irqsave(&trc->lock, flags);
	if (trc->rd_idx == trc->wr_idx) {
		spin_unlock_irqrestore(&trc->lock, flags);

		return -1;
	}
	td = &trc->buf[trc->rd_idx];

	if (td->ts == 0) {
		/* write in progress. */
		spin_unlock_irqrestore(&trc->lock, flags);

		return -1;
	}

	trc->rd_idx++;
	if (trc->rd_idx == trc->max_idx)
		trc->rd_idx = 0;
	spin_unlock_irqrestore(&trc->lock, flags);

	return snic_fmt_trc_data(td, buf, buf_sz);
}