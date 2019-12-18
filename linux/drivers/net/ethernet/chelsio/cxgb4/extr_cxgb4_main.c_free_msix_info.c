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
struct TYPE_2__ {int /*<<< orphan*/  msix_bmap; } ;
struct adapter {TYPE_1__ msix_bmap_ulds; int /*<<< orphan*/  msix_info_ulds; scalar_t__ num_ofld_uld; scalar_t__ num_uld; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_msix_info(struct adapter *adap)
{
	if (!(adap->num_uld && adap->num_ofld_uld))
		return;

	kfree(adap->msix_info_ulds);
	kfree(adap->msix_bmap_ulds.msix_bmap);
}