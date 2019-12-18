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

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hwrng_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zcrypt_rng_buffer ; 
 int /*<<< orphan*/  zcrypt_rng_dev ; 
 scalar_t__ zcrypt_rng_device_count ; 
 int /*<<< orphan*/  zcrypt_rng_mutex ; 

void zcrypt_rng_device_remove(void)
{
	mutex_lock(&zcrypt_rng_mutex);
	zcrypt_rng_device_count--;
	if (zcrypt_rng_device_count == 0) {
		hwrng_unregister(&zcrypt_rng_dev);
		free_page((unsigned long) zcrypt_rng_buffer);
	}
	mutex_unlock(&zcrypt_rng_mutex);
}