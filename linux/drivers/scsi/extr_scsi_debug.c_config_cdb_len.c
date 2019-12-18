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
struct scsi_device {int use_10_for_rw; int use_16_for_rw; int use_10_for_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sdebug_cdb_len ; 

__attribute__((used)) static void config_cdb_len(struct scsi_device *sdev)
{
	switch (sdebug_cdb_len) {
	case 6:	/* suggest 6 byte READ, WRITE and MODE SENSE/SELECT */
		sdev->use_10_for_rw = false;
		sdev->use_16_for_rw = false;
		sdev->use_10_for_ms = false;
		break;
	case 10: /* suggest 10 byte RWs and 6 byte MODE SENSE/SELECT */
		sdev->use_10_for_rw = true;
		sdev->use_16_for_rw = false;
		sdev->use_10_for_ms = false;
		break;
	case 12: /* suggest 10 byte RWs and 10 byte MODE SENSE/SELECT */
		sdev->use_10_for_rw = true;
		sdev->use_16_for_rw = false;
		sdev->use_10_for_ms = true;
		break;
	case 16:
		sdev->use_10_for_rw = false;
		sdev->use_16_for_rw = true;
		sdev->use_10_for_ms = true;
		break;
	case 32: /* No knobs to suggest this so same as 16 for now */
		sdev->use_10_for_rw = false;
		sdev->use_16_for_rw = true;
		sdev->use_10_for_ms = true;
		break;
	default:
		pr_warn("unexpected cdb_len=%d, force to 10\n",
			sdebug_cdb_len);
		sdev->use_10_for_rw = true;
		sdev->use_16_for_rw = false;
		sdev->use_10_for_ms = false;
		sdebug_cdb_len = 10;
		break;
	}
}