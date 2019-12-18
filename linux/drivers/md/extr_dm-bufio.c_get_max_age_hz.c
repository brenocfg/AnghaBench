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

/* Variables and functions */
 unsigned int HZ ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  dm_bufio_max_age ; 

__attribute__((used)) static unsigned get_max_age_hz(void)
{
	unsigned max_age = READ_ONCE(dm_bufio_max_age);

	if (max_age > UINT_MAX / HZ)
		max_age = UINT_MAX / HZ;

	return max_age * HZ;
}