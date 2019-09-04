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
typedef  int u16 ;
struct octeon_device {int rev_id; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 OCTEON_MAJOR_REV(struct octeon_device *oct)
{
	u16 rev = (oct->rev_id & 0xC) >> 2;

	return (rev == 0) ? 1 : rev;
}