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
struct pqi_scsi_dev {int in_reset; } ;

/* Variables and functions */

__attribute__((used)) static inline void pqi_device_reset_done(struct pqi_scsi_dev *device)
{
	device->in_reset = false;
}