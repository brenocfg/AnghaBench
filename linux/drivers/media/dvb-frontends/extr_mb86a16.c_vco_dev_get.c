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
struct mb86a16_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char vco_dev_get(struct mb86a16_state *state, int smrt)
{
	unsigned char R;

	if (smrt > 9375)
		R = 0;
	else
		R = 1;

	return R;
}