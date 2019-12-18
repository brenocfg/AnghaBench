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
struct mv88e6xxx_hw_stat {int type; int /*<<< orphan*/  string; } ;
struct mv88e6xxx_chip {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mv88e6xxx_hw_stat*) ; 
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mv88e6xxx_hw_stat* mv88e6xxx_hw_stats ; 

__attribute__((used)) static int mv88e6xxx_stats_get_strings(struct mv88e6xxx_chip *chip,
				       uint8_t *data, int types)
{
	struct mv88e6xxx_hw_stat *stat;
	int i, j;

	for (i = 0, j = 0; i < ARRAY_SIZE(mv88e6xxx_hw_stats); i++) {
		stat = &mv88e6xxx_hw_stats[i];
		if (stat->type & types) {
			memcpy(data + j * ETH_GSTRING_LEN, stat->string,
			       ETH_GSTRING_LEN);
			j++;
		}
	}

	return j;
}