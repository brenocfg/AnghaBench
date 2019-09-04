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
struct drm_selftest {int enabled; } ;

/* Variables and functions */

__attribute__((used)) static void set_default_test_all(struct drm_selftest *st, unsigned long count)
{
	unsigned long i;

	for (i = 0; i < count; i++)
		if (st[i].enabled)
			return;

	for (i = 0; i < count; i++)
		st[i].enabled = true;
}