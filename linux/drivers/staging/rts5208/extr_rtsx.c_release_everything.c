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
struct rtsx_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtsx_release_resources (struct rtsx_dev*) ; 
 int /*<<< orphan*/  rtsx_to_host (struct rtsx_dev*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_everything(struct rtsx_dev *dev)
{
	rtsx_release_resources(dev);

	/*
	 * Drop our reference to the host; the SCSI core will free it
	 * when the refcount becomes 0.
	 */
	scsi_host_put(rtsx_to_host(dev));
}