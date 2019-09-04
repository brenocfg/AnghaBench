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
struct hwrng {int dummy; } ;
struct hisi_rng {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RNG_RAN_NUM ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct hisi_rng* to_hisi_rng (struct hwrng*) ; 

__attribute__((used)) static int hisi_rng_read(struct hwrng *rng, void *buf, size_t max, bool wait)
{
	struct hisi_rng *hrng = to_hisi_rng(rng);
	u32 *data = buf;

	*data = readl_relaxed(hrng->base + RNG_RAN_NUM);
	return 4;
}