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
typedef  scalar_t__ u_int ;
struct ahd_softc {int msgout_len; scalar_t__ msgout_index; scalar_t__ msgout_buf; } ;
struct ahd_devinfo {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 scalar_t__ AHD_ASYNC_XFER_PERIOD ; 
 scalar_t__ AHD_SYNCRATE_PACED ; 
 scalar_t__ MSG_EXT_PPR_PCOMP_EN ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ spi_populate_ppr_msg (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahd_construct_ppr(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		  u_int period, u_int offset, u_int bus_width,
		  u_int ppr_options)
{
	/*
	 * Always request precompensation from
	 * the other target if we are running
	 * at paced syncrates.
	 */
	if (period <= AHD_SYNCRATE_PACED)
		ppr_options |= MSG_EXT_PPR_PCOMP_EN;
	if (offset == 0)
		period = AHD_ASYNC_XFER_PERIOD;
	ahd->msgout_index += spi_populate_ppr_msg(
			ahd->msgout_buf + ahd->msgout_index, period, offset,
			bus_width, ppr_options);
	ahd->msgout_len += 8;
	if (bootverbose) {
		printk("(%s:%c:%d:%d): Sending PPR bus_width %x, period %x, "
		       "offset %x, ppr_options %x\n", ahd_name(ahd),
		       devinfo->channel, devinfo->target, devinfo->lun,
		       bus_width, period, offset, ppr_options);
	}
}