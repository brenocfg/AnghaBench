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
struct TYPE_2__ {scalar_t__ major_version; scalar_t__ minor_version; } ;
struct mei_device {TYPE_1__ version; } ;

/* Variables and functions */
 scalar_t__ HBM_MAJOR_VERSION ; 
 scalar_t__ HBM_MINOR_VERSION ; 

bool mei_hbm_version_is_supported(struct mei_device *dev)
{
	return	(dev->version.major_version < HBM_MAJOR_VERSION) ||
		(dev->version.major_version == HBM_MAJOR_VERSION &&
		 dev->version.minor_version <= HBM_MINOR_VERSION);
}