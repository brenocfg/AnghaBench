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
struct circ_buf {char* buf; size_t tail; } ;
struct TYPE_2__ {struct circ_buf in_crc; } ;

/* Variables and functions */
 int ACPI_AML_BUF_SIZE ; 
 int /*<<< orphan*/  ACPI_AML_IN_KERN ; 
 TYPE_1__ acpi_aml_io ; 
 int acpi_aml_lock_read (struct circ_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_aml_unlock_fifo (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int acpi_aml_readb_kern(void)
{
	int ret;
	struct circ_buf *crc = &acpi_aml_io.in_crc;
	char *p;

	ret = acpi_aml_lock_read(crc, ACPI_AML_IN_KERN);
	if (ret < 0)
		return ret;
	/* sync head before removing cmds */
	smp_rmb();
	p = &crc->buf[crc->tail];
	ret = (int)*p;
	/* sync tail before inserting cmds */
	smp_mb();
	crc->tail = (crc->tail + 1) & (ACPI_AML_BUF_SIZE - 1);
	acpi_aml_unlock_fifo(ACPI_AML_IN_KERN, true);
	return ret;
}