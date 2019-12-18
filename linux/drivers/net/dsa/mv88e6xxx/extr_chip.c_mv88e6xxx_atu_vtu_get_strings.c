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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/ * mv88e6xxx_atu_vtu_stats_strings ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mv88e6xxx_atu_vtu_get_strings(uint8_t *data)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(mv88e6xxx_atu_vtu_stats_strings); i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			mv88e6xxx_atu_vtu_stats_strings[i],
			ETH_GSTRING_LEN);
}