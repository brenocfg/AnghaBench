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
struct virtrng_info {int /*<<< orphan*/  have_data; scalar_t__ busy; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_cleanup(struct hwrng *rng)
{
	struct virtrng_info *vi = (struct virtrng_info *)rng->priv;

	if (vi->busy)
		wait_for_completion(&vi->have_data);
}