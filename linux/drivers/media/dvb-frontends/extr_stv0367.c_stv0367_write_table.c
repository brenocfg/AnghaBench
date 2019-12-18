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
struct stv0367_state {int dummy; } ;
struct st_register {int /*<<< orphan*/  value; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0367_writereg (struct stv0367_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stv0367_write_table(struct stv0367_state *state,
				const struct st_register *deftab)
{
	int i = 0;

	while (1) {
		if (!deftab[i].addr)
			break;
		stv0367_writereg(state, deftab[i].addr, deftab[i].value);
		i++;
	}
}