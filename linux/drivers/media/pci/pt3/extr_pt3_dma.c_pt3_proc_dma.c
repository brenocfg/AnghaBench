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
typedef  scalar_t__ u8 ;
struct pt3_adapter {int buf_idx; int buf_ofs; scalar_t__ num_discard; int /*<<< orphan*/  demux; TYPE_1__* buffer; } ;
struct TYPE_2__ {scalar_t__* data; } ;

/* Variables and functions */
 int DATA_BUF_SZ ; 
 int PT3_ACCESS_UNIT ; 
 scalar_t__ PT3_BUF_CANARY ; 
 int TS_PACKET_SZ ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_packets (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__* next_unit (struct pt3_adapter*,int*,int*) ; 

int pt3_proc_dma(struct pt3_adapter *adap)
{
	int idx, ofs;

	idx = adap->buf_idx;
	ofs = adap->buf_ofs;

	if (adap->buffer[idx].data[ofs] == PT3_BUF_CANARY)
		return 0;

	while (*next_unit(adap, &idx, &ofs) != PT3_BUF_CANARY) {
		u8 *p;

		p = &adap->buffer[adap->buf_idx].data[adap->buf_ofs];
		if (adap->num_discard > 0)
			adap->num_discard--;
		else if (adap->buf_ofs + PT3_ACCESS_UNIT > DATA_BUF_SZ) {
			dvb_dmx_swfilter_packets(&adap->demux, p,
				(DATA_BUF_SZ - adap->buf_ofs) / TS_PACKET_SZ);
			dvb_dmx_swfilter_packets(&adap->demux,
				adap->buffer[idx].data, ofs / TS_PACKET_SZ);
		} else
			dvb_dmx_swfilter_packets(&adap->demux, p,
				PT3_ACCESS_UNIT / TS_PACKET_SZ);

		*p = PT3_BUF_CANARY;
		adap->buf_idx = idx;
		adap->buf_ofs = ofs;
	}
	return 0;
}