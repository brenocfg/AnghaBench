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
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_promisc_tcam_disable (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_promisc_tcam_enable (struct dsaf_device*,int /*<<< orphan*/ ) ; 

void hns_dsaf_set_promisc_tcam(struct dsaf_device *dsaf_dev,
			       u32 port, bool enable)
{
	if (enable)
		set_promisc_tcam_enable(dsaf_dev, port);
	else
		set_promisc_tcam_disable(dsaf_dev, port);
}