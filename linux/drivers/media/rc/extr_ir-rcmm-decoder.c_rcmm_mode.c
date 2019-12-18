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
struct rcmm_dec {int bits; } ;

/* Variables and functions */

__attribute__((used)) static bool rcmm_mode(const struct rcmm_dec *data)
{
	return !((0x000c0000 & data->bits) == 0x000c0000);
}