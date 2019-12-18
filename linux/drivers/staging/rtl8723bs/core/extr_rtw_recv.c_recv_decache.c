#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int priority; int seq_num; int frag_num; } ;
struct TYPE_6__ {TYPE_1__ attrib; } ;
struct TYPE_5__ {TYPE_3__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct stainfo_rxcache {scalar_t__* tid_rxseq; } ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 

sint recv_decache(union recv_frame *precv_frame, u8 bretry, struct stainfo_rxcache *prxcache)
{
	sint tid = precv_frame->u.hdr.attrib.priority;

	u16 seq_ctrl = ((precv_frame->u.hdr.attrib.seq_num&0xffff) << 4) |
		(precv_frame->u.hdr.attrib.frag_num & 0xf);

	if (tid > 15) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("recv_decache, (tid>15)! seq_ctrl = 0x%x, tid = 0x%x\n", seq_ctrl, tid));

		return _FAIL;
	}

	if (1) { /* if (bretry) */
		if (seq_ctrl == prxcache->tid_rxseq[tid]) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("recv_decache, seq_ctrl = 0x%x, tid = 0x%x, tid_rxseq = 0x%x\n", seq_ctrl, tid, prxcache->tid_rxseq[tid]));

			return _FAIL;
		}
	}

	prxcache->tid_rxseq[tid] = seq_ctrl;

	return _SUCCESS;

}