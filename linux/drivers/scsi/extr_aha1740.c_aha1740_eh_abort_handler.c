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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int SUCCESS ; 

__attribute__((used)) static int aha1740_eh_abort_handler (struct scsi_cmnd *dummy)
{
/*
 * From Alan Cox :
 * The AHA1740 has firmware handled abort/reset handling. The "head in
 * sand" kernel code is correct for once 8)
 *
 * So we define a dummy handler just to keep the kernel SCSI code as
 * quiet as possible...
 */

	return SUCCESS;
}