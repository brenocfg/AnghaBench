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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */

__attribute__((used)) static u16 cyapa_gen3_csum(const u8 *buf, size_t count)
{
	int i;
	u16 csum = 0;

	for (i = 0; i < count; i++)
		csum += buf[i];

	return csum;
}