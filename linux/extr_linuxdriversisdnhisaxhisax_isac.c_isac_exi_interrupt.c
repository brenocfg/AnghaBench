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
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,...) ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  ISAC_EXIR ; 
 unsigned char ISAC_EXIR_MOS ; 
 unsigned char ISAC_EXIR_XDU ; 
 unsigned char ISAC_EXIR_XMR ; 
 int /*<<< orphan*/  ISAC_MOSR ; 
 int /*<<< orphan*/  isac_retransmit (struct isac*) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 unsigned char stub2 (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isac_exi_interrupt(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISAC_EXIR);
	DBG(2, "EXIR %#x", val);

	if (val & ISAC_EXIR_XMR) {
		DBG(DBG_WARN, "ISAC XMR");
		isac_retransmit(isac);
	}
	if (val & ISAC_EXIR_XDU) {
		DBG(DBG_WARN, "ISAC XDU");
		isac_retransmit(isac);
	}
	if (val & ISAC_EXIR_MOS) {  /* MOS */
		DBG(DBG_WARN, "MOS");
		val = isac->read_isac(isac, ISAC_MOSR);
		DBG(2, "ISAC MOSR %#x", val);
	}
}