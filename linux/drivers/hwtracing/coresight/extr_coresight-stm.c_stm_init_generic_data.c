#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* name; int sw_start; int sw_end; int hw_override; int /*<<< orphan*/  set_options; int /*<<< orphan*/  unlink; int /*<<< orphan*/  link; int /*<<< orphan*/  mmio_addr; int /*<<< orphan*/  packet; int /*<<< orphan*/  sw_mmiosz; int /*<<< orphan*/  sw_nchannels; } ;
struct stm_drvdata {TYPE_1__ stm; int /*<<< orphan*/  numsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_PER_CHANNEL ; 
 int /*<<< orphan*/  stm_generic_link ; 
 int /*<<< orphan*/  stm_generic_packet ; 
 int /*<<< orphan*/  stm_generic_set_options ; 
 int /*<<< orphan*/  stm_generic_unlink ; 
 int /*<<< orphan*/  stm_mmio_addr ; 

__attribute__((used)) static void stm_init_generic_data(struct stm_drvdata *drvdata,
				  const char *name)
{
	drvdata->stm.name = name;

	/*
	 * MasterIDs are assigned at HW design phase. As such the core is
	 * using a single master for interaction with this device.
	 */
	drvdata->stm.sw_start = 1;
	drvdata->stm.sw_end = 1;
	drvdata->stm.hw_override = true;
	drvdata->stm.sw_nchannels = drvdata->numsp;
	drvdata->stm.sw_mmiosz = BYTES_PER_CHANNEL;
	drvdata->stm.packet = stm_generic_packet;
	drvdata->stm.mmio_addr = stm_mmio_addr;
	drvdata->stm.link = stm_generic_link;
	drvdata->stm.unlink = stm_generic_unlink;
	drvdata->stm.set_options = stm_generic_set_options;
}