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
typedef  int uint64_t ;
typedef  int u64 ;
typedef  int u16 ;
struct mv88e6xxx_chip {int /*<<< orphan*/  dev; } ;
struct mv88e6352_serdes_hw_stat {int sizeof_stat; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mv88e6352_serdes_read (struct mv88e6xxx_chip*,scalar_t__,int*) ; 

__attribute__((used)) static uint64_t mv88e6352_serdes_get_stat(struct mv88e6xxx_chip *chip,
					  struct mv88e6352_serdes_hw_stat *stat)
{
	u64 val = 0;
	u16 reg;
	int err;

	err = mv88e6352_serdes_read(chip, stat->reg, &reg);
	if (err) {
		dev_err(chip->dev, "failed to read statistic\n");
		return 0;
	}

	val = reg;

	if (stat->sizeof_stat == 32) {
		err = mv88e6352_serdes_read(chip, stat->reg + 1, &reg);
		if (err) {
			dev_err(chip->dev, "failed to read statistic\n");
			return 0;
		}
		val = val << 16 | reg;
	}

	return val;
}