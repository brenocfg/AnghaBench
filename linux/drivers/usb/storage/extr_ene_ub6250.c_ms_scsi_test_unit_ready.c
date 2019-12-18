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
struct us_data {scalar_t__ extra; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_2__ {scalar_t__ Ready; scalar_t__ Insert; } ;
struct ene_ub6250_info {TYPE_1__ MS_Status; } ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  ene_ms_init (struct us_data*) ; 

__attribute__((used)) static int ms_scsi_test_unit_ready(struct us_data *us, struct scsi_cmnd *srb)
{
	struct ene_ub6250_info *info = (struct ene_ub6250_info *)(us->extra);

	/* pr_info("MS_SCSI_Test_Unit_Ready\n"); */
	if (info->MS_Status.Insert && info->MS_Status.Ready) {
		return USB_STOR_TRANSPORT_GOOD;
	} else {
		ene_ms_init(us);
		return USB_STOR_TRANSPORT_GOOD;
	}

	return USB_STOR_TRANSPORT_GOOD;
}