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
struct stv090x_internal {int dummy; } ;
struct stv090x_dev {struct stv090x_dev* next_dev; struct stv090x_internal* internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct stv090x_dev* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct stv090x_dev* stv090x_first_dev ; 

__attribute__((used)) static struct stv090x_dev *append_internal(struct stv090x_internal *internal)
{
	struct stv090x_dev *new_dev;
	struct stv090x_dev *temp_dev;

	new_dev = kmalloc(sizeof(struct stv090x_dev), GFP_KERNEL);
	if (new_dev != NULL) {
		new_dev->internal = internal;
		new_dev->next_dev = NULL;

		/* append to list */
		if (stv090x_first_dev == NULL) {
			stv090x_first_dev = new_dev;
		} else {
			temp_dev = stv090x_first_dev;
			while (temp_dev->next_dev != NULL)
				temp_dev = temp_dev->next_dev;

			temp_dev->next_dev = new_dev;
		}
	}

	return new_dev;
}