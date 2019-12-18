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
typedef  int /*<<< orphan*/  u16 ;
struct pmic8xxx_kp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  pmic8xxx_col_state (struct pmic8xxx_kp*,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int pmic8xxx_kp_read_data(struct pmic8xxx_kp *kp, u16 *state,
					u16 data_reg, int read_rows)
{
	int rc, row;
	unsigned int val;

	for (row = 0; row < read_rows; row++) {
		rc = regmap_read(kp->regmap, data_reg, &val);
		if (rc)
			return rc;
		dev_dbg(kp->dev, "%d = %d\n", row, val);
		state[row] = pmic8xxx_col_state(kp, val);
	}

	return 0;
}