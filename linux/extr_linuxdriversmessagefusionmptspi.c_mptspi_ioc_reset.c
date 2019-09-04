#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _MPT_SCSI_HOST {int dummy; } ;
struct TYPE_4__ {scalar_t__ bus_type; scalar_t__ sh; } ;
typedef  TYPE_1__ MPT_ADAPTER ;

/* Variables and functions */
 int MPT_IOC_POST_RESET ; 
 scalar_t__ SPI ; 
 int mptscsih_ioc_reset (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mptspi_dv_renegotiate (struct _MPT_SCSI_HOST*) ; 
 struct _MPT_SCSI_HOST* shost_priv (scalar_t__) ; 

__attribute__((used)) static int
mptspi_ioc_reset(MPT_ADAPTER *ioc, int reset_phase)
{
	int rc;

	rc = mptscsih_ioc_reset(ioc, reset_phase);
	if ((ioc->bus_type != SPI) || (!rc))
		return rc;

	/* only try to do a renegotiation if we're properly set up
	 * if we get an ioc fault on bringup, ioc->sh will be NULL */
	if (reset_phase == MPT_IOC_POST_RESET &&
	    ioc->sh) {
		struct _MPT_SCSI_HOST *hd = shost_priv(ioc->sh);

		mptspi_dv_renegotiate(hd);
	}

	return rc;
}