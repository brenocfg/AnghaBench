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
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned char) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  ISACSX_ISTA ; 
 unsigned char ISACSX_ISTA_CIC ; 
 unsigned char ISACSX_ISTA_ICD ; 
 int /*<<< orphan*/  isacsx_cic_interrupt (struct isac*) ; 
 int /*<<< orphan*/  isacsx_icd_interrupt (struct isac*) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 

void isacsx_irq(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISACSX_ISTA);
	DBG(DBG_IRQ, "ISTA %#x", val);

	if (val & ISACSX_ISTA_ICD)
		isacsx_icd_interrupt(isac);
	if (val & ISACSX_ISTA_CIC)
		isacsx_cic_interrupt(isac);
}