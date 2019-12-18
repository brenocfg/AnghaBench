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
struct stv090x_internal {int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  i2c_adap; } ;
struct stv090x_dev {struct stv090x_dev* next_dev; } ;

/* Variables and functions */
 struct stv090x_dev* find_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct stv090x_dev*) ; 
 struct stv090x_dev* stv090x_first_dev ; 

__attribute__((used)) static void remove_dev(struct stv090x_internal *internal)
{
	struct stv090x_dev *prev_dev = stv090x_first_dev;
	struct stv090x_dev *del_dev = find_dev(internal->i2c_adap,
						internal->i2c_addr);

	if (del_dev != NULL) {
		if (del_dev == stv090x_first_dev) {
			stv090x_first_dev = del_dev->next_dev;
		} else {
			while (prev_dev->next_dev != del_dev)
				prev_dev = prev_dev->next_dev;

			prev_dev->next_dev = del_dev->next_dev;
		}

		kfree(del_dev);
	}
}