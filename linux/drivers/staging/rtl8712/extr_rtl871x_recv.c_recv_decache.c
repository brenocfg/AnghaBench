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
struct TYPE_5__ {TYPE_1__ attrib; } ;
struct TYPE_6__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct stainfo_rxcache {scalar_t__* tid_rxseq; } ;
typedef  int sint ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 

__attribute__((used)) static sint recv_decache(union recv_frame *precv_frame, u8 bretry,
		  struct stainfo_rxcache *prxcache)
{
	sint tid = precv_frame->u.hdr.attrib.priority;
	u16 seq_ctrl = ((precv_frame->u.hdr.attrib.seq_num & 0xffff) << 4) |
			(precv_frame->u.hdr.attrib.frag_num & 0xf);

	if (tid > 15)
		return _FAIL;
	if (seq_ctrl == prxcache->tid_rxseq[tid])
		return _FAIL;
	prxcache->tid_rxseq[tid] = seq_ctrl;
	return _SUCCESS;
}