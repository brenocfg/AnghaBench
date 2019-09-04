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
typedef  int u32 ;
struct fritz_adapter {int (* read_hdlc_status ) (struct fritz_adapter*,int) ;int /*<<< orphan*/ * bcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,char,int) ; 
 int HDLC_INT_MASK ; 
 int /*<<< orphan*/  hdlc_irq_one (int /*<<< orphan*/ *,int) ; 
 int stub1 (struct fritz_adapter*,int) ; 

__attribute__((used)) static inline void hdlc_irq(struct fritz_adapter *adapter)
{
	int nr;
	u32 stat;

	for (nr = 0; nr < 2; nr++) {
		stat = adapter->read_hdlc_status(adapter, nr);
		DBG(0x10, "HDLC %c stat %#x", 'A' + nr, stat);
		if (stat & HDLC_INT_MASK)
			hdlc_irq_one(&adapter->bcs[nr], stat);
	}
}