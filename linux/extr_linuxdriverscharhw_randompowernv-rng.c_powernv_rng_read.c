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
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  powernv_get_random_long (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int powernv_rng_read(struct hwrng *rng, void *data, size_t max, bool wait)
{
	unsigned long *buf;
	int i, len;

	/* We rely on rng_buffer_size() being >= sizeof(unsigned long) */
	len = max / sizeof(unsigned long);

	buf = (unsigned long *)data;

	for (i = 0; i < len; i++)
		powernv_get_random_long(buf++);

	return len * sizeof(unsigned long);
}