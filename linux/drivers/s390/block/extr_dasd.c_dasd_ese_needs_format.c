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
typedef  int u8 ;
struct irb {int /*<<< orphan*/  scsw; } ;
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_block {struct dasd_device* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* is_ese ) (struct dasd_device*) ;} ;

/* Variables and functions */
 scalar_t__ SCHN_STAT_INCORR_LEN ; 
 int SNS1_FILE_PROTECTED ; 
 int SNS1_NO_REC_FOUND ; 
 int* dasd_get_sense (struct irb*) ; 
 scalar_t__ scsw_cstat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dasd_device*) ; 

__attribute__((used)) static int dasd_ese_needs_format(struct dasd_block *block, struct irb *irb)
{
	struct dasd_device *device = NULL;
	u8 *sense = NULL;

	if (!block)
		return 0;
	device = block->base;
	if (!device || !device->discipline->is_ese)
		return 0;
	if (!device->discipline->is_ese(device))
		return 0;

	sense = dasd_get_sense(irb);
	if (!sense)
		return 0;

	return !!(sense[1] & SNS1_NO_REC_FOUND) ||
		!!(sense[1] & SNS1_FILE_PROTECTED) ||
		scsw_cstat(&irb->scsw) == SCHN_STAT_INCORR_LEN;
}