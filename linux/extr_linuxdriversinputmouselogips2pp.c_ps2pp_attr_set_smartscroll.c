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
struct psmouse {unsigned int smartscroll; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  ps2pp_set_smartscroll (struct psmouse*,unsigned int) ; 

__attribute__((used)) static ssize_t ps2pp_attr_set_smartscroll(struct psmouse *psmouse, void *data,
					  const char *buf, size_t count)
{
	unsigned int value;
	int err;

	err = kstrtouint(buf, 10, &value);
	if (err)
		return err;

	if (value > 1)
		return -EINVAL;

	ps2pp_set_smartscroll(psmouse, value);
	psmouse->smartscroll = value;
	return count;
}