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
struct device {int dummy; } ;
struct caam_drv_private_jr {int /*<<< orphan*/  tfm_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 

void caam_jr_free(struct device *rdev)
{
	struct caam_drv_private_jr *jrpriv = dev_get_drvdata(rdev);

	atomic_dec(&jrpriv->tfm_count);
}