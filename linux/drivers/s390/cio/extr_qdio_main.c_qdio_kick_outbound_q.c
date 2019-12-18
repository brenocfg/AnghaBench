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
struct qdio_q {int /*<<< orphan*/  nr; int /*<<< orphan*/  irq_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int EBUSY ; 
 int EIO ; 
 int ENOBUFS ; 
 int QDIO_BUSY_BIT_RETRIES ; 
 int /*<<< orphan*/  QDIO_BUSY_BIT_RETRY_DELAY ; 
 int /*<<< orphan*/  SCH_NO (struct qdio_q*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  need_siga_out (struct qdio_q*) ; 
 int qdio_siga_output (struct qdio_q*,unsigned int*,unsigned long) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siga_write ; 

__attribute__((used)) static int qdio_kick_outbound_q(struct qdio_q *q, unsigned long aob)
{
	int retries = 0, cc;
	unsigned int busy_bit;

	if (!need_siga_out(q))
		return 0;

	DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-w:%1d", q->nr);
retry:
	qperf_inc(q, siga_write);

	cc = qdio_siga_output(q, &busy_bit, aob);
	switch (cc) {
	case 0:
		break;
	case 2:
		if (busy_bit) {
			while (++retries < QDIO_BUSY_BIT_RETRIES) {
				mdelay(QDIO_BUSY_BIT_RETRY_DELAY);
				goto retry;
			}
			DBF_ERROR("%4x cc2 BBC:%1d", SCH_NO(q), q->nr);
			cc = -EBUSY;
		} else {
			DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "siga-w cc2:%1d", q->nr);
			cc = -ENOBUFS;
		}
		break;
	case 1:
	case 3:
		DBF_ERROR("%4x SIGA-W:%1d", SCH_NO(q), cc);
		cc = -EIO;
		break;
	}
	if (retries) {
		DBF_ERROR("%4x cc2 BB2:%1d", SCH_NO(q), q->nr);
		DBF_ERROR("count:%u", retries);
	}
	return cc;
}