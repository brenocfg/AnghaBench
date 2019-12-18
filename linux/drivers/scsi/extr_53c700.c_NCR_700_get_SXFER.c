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
struct scsi_device {int /*<<< orphan*/  sdev_target; TYPE_1__* host; } ;
struct NCR_700_Host_Parameters {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCR_700_offset_period_to_sxfer (struct NCR_700_Host_Parameters*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_period (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u8
NCR_700_get_SXFER(struct scsi_device *SDp)
{
	struct NCR_700_Host_Parameters *hostdata = 
		(struct NCR_700_Host_Parameters *)SDp->host->hostdata[0];

	return NCR_700_offset_period_to_sxfer(hostdata,
					      spi_offset(SDp->sdev_target),
					      spi_period(SDp->sdev_target));
}