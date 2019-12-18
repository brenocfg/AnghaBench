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
struct iss_device {scalar_t__ ref_count; int /*<<< orphan*/  iss_mutex; } ;

/* Variables and functions */
 scalar_t__ iss_enable_clocks (struct iss_device*) ; 
 int /*<<< orphan*/  iss_enable_interrupts (struct iss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct iss_device *omap4iss_get(struct iss_device *iss)
{
	struct iss_device *__iss = iss;

	if (!iss)
		return NULL;

	mutex_lock(&iss->iss_mutex);
	if (iss->ref_count > 0)
		goto out;

	if (iss_enable_clocks(iss) < 0) {
		__iss = NULL;
		goto out;
	}

	iss_enable_interrupts(iss);

out:
	if (__iss)
		iss->ref_count++;
	mutex_unlock(&iss->iss_mutex);

	return __iss;
}