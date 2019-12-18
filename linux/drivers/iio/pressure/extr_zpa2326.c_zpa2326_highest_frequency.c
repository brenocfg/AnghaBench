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
struct zpa2326_frequency {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct zpa2326_frequency const*) ; 
 struct zpa2326_frequency const* zpa2326_sampling_frequencies ; 

__attribute__((used)) static const struct zpa2326_frequency *zpa2326_highest_frequency(void)
{
	return &zpa2326_sampling_frequencies[
		ARRAY_SIZE(zpa2326_sampling_frequencies) - 1];
}