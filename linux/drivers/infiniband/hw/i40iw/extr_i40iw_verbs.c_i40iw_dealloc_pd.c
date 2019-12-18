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
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct i40iw_pd {int dummy; } ;
struct i40iw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_rem_pdusecount (struct i40iw_pd*,struct i40iw_device*) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 
 struct i40iw_pd* to_iwpd (struct ib_pd*) ; 

__attribute__((used)) static void i40iw_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct i40iw_pd *iwpd = to_iwpd(ibpd);
	struct i40iw_device *iwdev = to_iwdev(ibpd->device);

	i40iw_rem_pdusecount(iwpd, iwdev);
}