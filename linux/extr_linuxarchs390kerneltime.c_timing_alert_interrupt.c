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
struct stp_irq_parm {int dummy; } ;
struct ext_code {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEXT_TLA ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stp_timing_alert (struct stp_irq_parm*) ; 

__attribute__((used)) static void timing_alert_interrupt(struct ext_code ext_code,
				   unsigned int param32, unsigned long param64)
{
	inc_irq_stat(IRQEXT_TLA);
	if (param32 & 0x00038000)
		stp_timing_alert((struct stp_irq_parm *) &param32);
}