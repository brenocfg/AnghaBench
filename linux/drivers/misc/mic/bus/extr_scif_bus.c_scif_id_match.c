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
struct scif_hw_dev_id {scalar_t__ device; scalar_t__ vendor; } ;
struct TYPE_2__ {scalar_t__ device; scalar_t__ vendor; } ;
struct scif_hw_dev {TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ SCIF_DEV_ANY_ID ; 

__attribute__((used)) static inline int scif_id_match(const struct scif_hw_dev *dev,
				const struct scif_hw_dev_id *id)
{
	if (id->device != dev->id.device && id->device != SCIF_DEV_ANY_ID)
		return 0;

	return id->vendor == SCIF_DEV_ANY_ID || id->vendor == dev->id.vendor;
}