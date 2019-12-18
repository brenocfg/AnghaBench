#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  truesize; } ;
typedef  TYPE_1__ _pkt ;
typedef  int /*<<< orphan*/  _nic_hdl ;

/* Variables and functions */
 int /*<<< orphan*/  MSTAT_ALLOC_SUCCESS ; 
 int /*<<< orphan*/  MSTAT_TYPE_SKB ; 
 int _rtw_xmit_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_mstat_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_xmit_entry(_pkt *pkt, _nic_hdl pnetdev)
{
	int ret = 0;

	if (pkt) {
		rtw_mstat_update(MSTAT_TYPE_SKB, MSTAT_ALLOC_SUCCESS, pkt->truesize);
		ret = _rtw_xmit_entry(pkt, pnetdev);
	}

	return ret;
}