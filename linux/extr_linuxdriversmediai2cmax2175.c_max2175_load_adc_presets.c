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
struct max2175 {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** adc_presets ; 
 int /*<<< orphan*/  max2175_write (struct max2175*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max2175_load_adc_presets(struct max2175 *ctx)
{
	unsigned int i, j;

	for (i = 0; i < ARRAY_SIZE(adc_presets); i++)
		for (j = 0; j < ARRAY_SIZE(adc_presets[0]); j++)
			max2175_write(ctx, 146 + j + i * 55, adc_presets[i][j]);
}