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
typedef  int /*<<< orphan*/  u64 ;
struct scsi_qla_host {unsigned char* node_name; unsigned char* port_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static void qlt_lport_dump(struct scsi_qla_host *vha, u64 wwpn,
	unsigned char *b)
{
	pr_debug("qla2xxx HW vha->node_name: %8phC\n", vha->node_name);
	pr_debug("qla2xxx HW vha->port_name: %8phC\n", vha->port_name);
	put_unaligned_be64(wwpn, b);
	pr_debug("qla2xxx passed configfs WWPN: %8phC\n", b);
}