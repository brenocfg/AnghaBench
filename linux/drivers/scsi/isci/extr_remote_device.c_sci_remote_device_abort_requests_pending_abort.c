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
struct isci_remote_device {int dummy; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 int sci_remote_device_terminate_reqs_checkabort (struct isci_remote_device*,int) ; 

enum sci_status sci_remote_device_abort_requests_pending_abort(
	struct isci_remote_device *idev)
{
	return sci_remote_device_terminate_reqs_checkabort(idev, 1);
}