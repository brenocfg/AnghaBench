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
struct mv88e6xxx_chip {int dummy; } ;
struct mv88e6352_serdes_hw_stat {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mv88e6352_serdes_hw_stat*) ; 
 int ETH_GSTRING_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv88e6352_port_has_serdes (struct mv88e6xxx_chip*,int) ; 
 struct mv88e6352_serdes_hw_stat* mv88e6352_serdes_hw_stats ; 

int mv88e6352_serdes_get_strings(struct mv88e6xxx_chip *chip,
				 int port, uint8_t *data)
{
	struct mv88e6352_serdes_hw_stat *stat;
	int i;

	if (!mv88e6352_port_has_serdes(chip, port))
		return 0;

	for (i = 0; i < ARRAY_SIZE(mv88e6352_serdes_hw_stats); i++) {
		stat = &mv88e6352_serdes_hw_stats[i];
		memcpy(data + i * ETH_GSTRING_LEN, stat->string,
		       ETH_GSTRING_LEN);
	}
	return ARRAY_SIZE(mv88e6352_serdes_hw_stats);
}