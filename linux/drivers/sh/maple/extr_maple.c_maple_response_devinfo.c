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
struct maple_device {scalar_t__ unit; size_t port; } ;

/* Variables and functions */
 int* checked ; 
 int* empty ; 
 int /*<<< orphan*/  fullscan ; 
 int /*<<< orphan*/  maple_attach_driver (struct maple_device*) ; 
 int /*<<< orphan*/  maple_map_subunits (struct maple_device*,char) ; 
 int scanning ; 
 int /*<<< orphan*/  started ; 
 char* subdevice_map ; 

__attribute__((used)) static void maple_response_devinfo(struct maple_device *mdev,
				   char *recvbuf)
{
	char submask;
	if (!started || (scanning == 2) || !fullscan) {
		if ((mdev->unit == 0) && (checked[mdev->port] == false)) {
			checked[mdev->port] = true;
			maple_attach_driver(mdev);
		} else {
			if (mdev->unit != 0)
				maple_attach_driver(mdev);
			if (mdev->unit == 0) {
				empty[mdev->port] = false;
				maple_attach_driver(mdev);
			}
		}
	}
	if (mdev->unit == 0) {
		submask = recvbuf[2] & 0x1F;
		if (submask ^ subdevice_map[mdev->port]) {
			maple_map_subunits(mdev, submask);
			subdevice_map[mdev->port] = submask;
		}
	}
}