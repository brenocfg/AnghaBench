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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FA_FLASH_LAYOUT_ADDR_82 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla4_8xxx_find_flt_start(struct scsi_qla_host *ha, uint32_t *start)
{
	const char *loc, *locations[] = { "DEF", "PCI" };

	/*
	 * FLT-location structure resides after the last PCI region.
	 */

	/* Begin with sane defaults. */
	loc = locations[0];
	*start = FA_FLASH_LAYOUT_ADDR_82;

	DEBUG2(ql4_printk(KERN_INFO, ha, "FLTL[%s] = 0x%x.\n", loc, *start));
	return QLA_SUCCESS;
}