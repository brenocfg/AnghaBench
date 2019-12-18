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
struct Scsi_Host {int dummy; } ;
struct NCR5380_hostdata {int id_mask; } ;

/* Variables and functions */
 int ICR_ASSERT_DATA ; 
 int ICR_ASSERT_SEL ; 
 int ICR_BASE ; 
 int /*<<< orphan*/  INITIATOR_COMMAND_REG ; 
 int NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTPUT_DATA_REG ; 
 int PHASE_MASK ; 
 int PHASE_SR_TO_TCR (int) ; 
 int /*<<< orphan*/  SELECT_ENABLE_REG ; 
 int /*<<< orphan*/  STATUS_REG ; 
 int /*<<< orphan*/  TARGET_COMMAND_REG ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct NCR5380_hostdata* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void g_NCR5380_trigger_irq(struct Scsi_Host *instance)
{
	struct NCR5380_hostdata *hostdata = shost_priv(instance);

	/*
	 * An interrupt is triggered whenever BSY = false, SEL = true
	 * and a bit set in the SELECT_ENABLE_REG is asserted on the
	 * SCSI bus.
	 *
	 * Note that the bus is only driven when the phase control signals
	 * (I/O, C/D, and MSG) match those in the TCR.
	 */
	NCR5380_write(TARGET_COMMAND_REG,
	              PHASE_SR_TO_TCR(NCR5380_read(STATUS_REG) & PHASE_MASK));
	NCR5380_write(SELECT_ENABLE_REG, hostdata->id_mask);
	NCR5380_write(OUTPUT_DATA_REG, hostdata->id_mask);
	NCR5380_write(INITIATOR_COMMAND_REG,
	              ICR_BASE | ICR_ASSERT_DATA | ICR_ASSERT_SEL);

	msleep(1);

	NCR5380_write(INITIATOR_COMMAND_REG, ICR_BASE);
	NCR5380_write(SELECT_ENABLE_REG, 0);
	NCR5380_write(TARGET_COMMAND_REG, 0);
}