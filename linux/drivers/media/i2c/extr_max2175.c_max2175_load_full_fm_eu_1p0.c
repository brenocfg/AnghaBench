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
struct max2175 {int decim_ratio; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * full_fm_eu_1p0 ; 
 int /*<<< orphan*/  max2175_write (struct max2175*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void max2175_load_full_fm_eu_1p0(struct max2175 *ctx)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(full_fm_eu_1p0); i++)
		max2175_write(ctx, i + 1, full_fm_eu_1p0[i]);

	usleep_range(5000, 5500);
	ctx->decim_ratio = 36;
}