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
struct rmi_device {int dummy; } ;

/* Variables and functions */
 int RMI4_MAX_PAGE ; 
 int RMI_SCAN_CONTINUE ; 
 int RMI_SCAN_DONE ; 
 int rmi_scan_pdt_page (struct rmi_device*,int,int*,void*,int (*) (struct rmi_device*,void*,struct pdt_entry const*)) ; 

int rmi_scan_pdt(struct rmi_device *rmi_dev, void *ctx,
		 int (*callback)(struct rmi_device *rmi_dev,
		 void *ctx, const struct pdt_entry *entry))
{
	int page;
	int empty_pages = 0;
	int retval = RMI_SCAN_DONE;

	for (page = 0; page <= RMI4_MAX_PAGE; page++) {
		retval = rmi_scan_pdt_page(rmi_dev, page, &empty_pages,
					   ctx, callback);
		if (retval != RMI_SCAN_CONTINUE)
			break;
	}

	return retval < 0 ? retval : 0;
}