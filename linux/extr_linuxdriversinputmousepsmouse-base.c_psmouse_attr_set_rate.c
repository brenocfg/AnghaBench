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
struct psmouse {int /*<<< orphan*/  (* set_rate ) (struct psmouse*,unsigned int) ;} ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*,unsigned int) ; 

__attribute__((used)) static ssize_t psmouse_attr_set_rate(struct psmouse *psmouse, void *data, const char *buf, size_t count)
{
	unsigned int value;
	int err;

	err = kstrtouint(buf, 10, &value);
	if (err)
		return err;

	psmouse->set_rate(psmouse, value);
	return count;
}