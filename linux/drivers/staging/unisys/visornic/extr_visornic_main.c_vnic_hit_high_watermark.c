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
typedef  scalar_t__ ulong ;
struct visornic_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ devdata_xmits_outstanding (struct visornic_devdata*) ; 

__attribute__((used)) static bool vnic_hit_high_watermark(struct visornic_devdata *devdata,
				    ulong high_watermark)
{
	return (devdata_xmits_outstanding(devdata) >= high_watermark);
}