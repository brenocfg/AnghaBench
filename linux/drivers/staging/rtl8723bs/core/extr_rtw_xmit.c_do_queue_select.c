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
typedef  int /*<<< orphan*/  u8 ;
struct pkt_attrib {int /*<<< orphan*/  qsel; int /*<<< orphan*/  priority; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 

__attribute__((used)) static void do_queue_select(struct adapter	*padapter, struct pkt_attrib *pattrib)
{
	u8 qsel;

	qsel = pattrib->priority;
	RT_TRACE(_module_rtl871x_xmit_c_, _drv_info_, ("### do_queue_select priority =%d , qsel = %d\n", pattrib->priority, qsel));

	pattrib->qsel = qsel;
}