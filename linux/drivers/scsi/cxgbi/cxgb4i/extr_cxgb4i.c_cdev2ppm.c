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
struct cxgbi_ppm {int dummy; } ;
struct cxgbi_device {int dummy; } ;
struct cxgb4_lld_info {scalar_t__* iscsi_ppm; } ;

/* Variables and functions */
 scalar_t__ cxgbi_cdev_priv (struct cxgbi_device*) ; 

__attribute__((used)) static struct cxgbi_ppm *cdev2ppm(struct cxgbi_device *cdev)
{
	return (struct cxgbi_ppm *)(*((struct cxgb4_lld_info *)
				       (cxgbi_cdev_priv(cdev)))->iscsi_ppm);
}