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
typedef  int /*<<< orphan*/  u8 ;
struct regdata {int /*<<< orphan*/  data; int /*<<< orphan*/  reg; } ;
struct mb86a20s_state {int dummy; } ;

/* Variables and functions */
 int mb86a20s_i2c_writereg (struct mb86a20s_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mb86a20s_i2c_writeregdata(struct mb86a20s_state *state,
				     u8 i2c_addr, struct regdata *rd, int size)
{
	int i, rc;

	for (i = 0; i < size; i++) {
		rc = mb86a20s_i2c_writereg(state, i2c_addr, rd[i].reg,
					   rd[i].data);
		if (rc < 0)
			return rc;
	}
	return 0;
}