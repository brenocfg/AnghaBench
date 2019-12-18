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
struct scsi_qla_host {int dummy; } ;
struct qla27xx_image_status {int /*<<< orphan*/  signature; int /*<<< orphan*/  checksum; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  ver_minor; int /*<<< orphan*/  ver_major; int /*<<< orphan*/  generation; int /*<<< orphan*/  image_status_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_init ; 

__attribute__((used)) static void
qla27xx_print_image(struct scsi_qla_host *vha, char *name,
    struct qla27xx_image_status *image_status)
{
	ql_dbg(ql_dbg_init, vha, 0x018b,
	    "%s %s: mask=%#02x gen=%#04x ver=%u.%u map=%#01x sum=%#08x sig=%#08x\n",
	    name, "status",
	    image_status->image_status_mask,
	    le16_to_cpu(image_status->generation),
	    image_status->ver_major,
	    image_status->ver_minor,
	    image_status->bitmap,
	    le32_to_cpu(image_status->checksum),
	    le32_to_cpu(image_status->signature));
}