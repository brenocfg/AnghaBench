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
struct zpci_report_error_header {int version; int action; int length; } ;
struct err_notify_sccb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 
#define  SCLP_ERRNOTIFY_AQ_INFO_LOG 130 
#define  SCLP_ERRNOTIFY_AQ_REPAIR 129 
#define  SCLP_ERRNOTIFY_AQ_RESET 128 

__attribute__((used)) static int sclp_pci_check_report(struct zpci_report_error_header *report)
{
	if (report->version != 1)
		return -EINVAL;

	switch (report->action) {
	case SCLP_ERRNOTIFY_AQ_RESET:
	case SCLP_ERRNOTIFY_AQ_REPAIR:
	case SCLP_ERRNOTIFY_AQ_INFO_LOG:
		break;
	default:
		return -EINVAL;
	}

	if (report->length > (PAGE_SIZE - sizeof(struct err_notify_sccb)))
		return -EINVAL;

	return 0;
}