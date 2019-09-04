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
typedef  int /*<<< orphan*/  u8 ;
struct pt3_adapter {int num_bufs; scalar_t__ buf_ofs; scalar_t__ buf_idx; TYPE_1__* buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DATA_BUF_SZ ; 
 scalar_t__ PT3_ACCESS_UNIT ; 
 int /*<<< orphan*/  PT3_BUF_CANARY ; 

void pt3_init_dmabuf(struct pt3_adapter *adap)
{
	int idx, ofs;
	u8 *p;

	idx = 0;
	ofs = 0;
	p = adap->buffer[0].data;
	/* mark the whole buffers as "not written yet" */
	while (idx < adap->num_bufs) {
		p[ofs] = PT3_BUF_CANARY;
		ofs += PT3_ACCESS_UNIT;
		if (ofs >= DATA_BUF_SZ) {
			ofs -= DATA_BUF_SZ;
			idx++;
			p = adap->buffer[idx].data;
		}
	}
	adap->buf_idx = 0;
	adap->buf_ofs = 0;
}