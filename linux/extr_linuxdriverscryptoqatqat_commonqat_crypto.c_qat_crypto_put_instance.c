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
struct qat_crypto_instance {int /*<<< orphan*/  accel_dev; int /*<<< orphan*/  refctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  adf_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

void qat_crypto_put_instance(struct qat_crypto_instance *inst)
{
	atomic_dec(&inst->refctr);
	adf_dev_put(inst->accel_dev);
}