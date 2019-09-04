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
struct hwrng {int /*<<< orphan*/  priv; } ;

/* Variables and functions */

__attribute__((used)) static int via_rng_data_read(struct hwrng *rng, u32 *data)
{
	u32 via_rng_datum = (u32)rng->priv;

	*data = via_rng_datum;

	return 1;
}