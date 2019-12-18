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
struct psmouse {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fsp_onpad_hscr (struct psmouse*,unsigned int) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 

__attribute__((used)) static ssize_t fsp_attr_set_hscroll(struct psmouse *psmouse, void *data,
					const char *buf, size_t count)
{
	unsigned int val;
	int err;

	err = kstrtouint(buf, 10, &val);
	if (err)
		return err;

	if (val > 1)
		return -EINVAL;

	fsp_onpad_hscr(psmouse, val);

	return count;
}