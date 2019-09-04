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
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  l1m; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ *,unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISACSX_CIR0 ; 
 unsigned char ISACSX_CIR0_CIC0 ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isacsx_cic_interrupt(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISACSX_CIR0);
	DBG(DBG_IRQ, "CIR0 %#x", val);
	if (val & ISACSX_CIR0_CIC0) {
		DBG(DBG_IRQ, "CODR0 %#x", val >> 4);
		FsmEvent(&isac->l1m, val >> 4, NULL);
	}
}