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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 scalar_t__ fsp_reg_write (struct psmouse*,unsigned int,unsigned int) ; 
 scalar_t__ fsp_reg_write_enable (struct psmouse*,int) ; 
 size_t kstrtouint (char*,int,unsigned int*) ; 
 unsigned int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static ssize_t fsp_attr_set_setreg(struct psmouse *psmouse, void *data,
				   const char *buf, size_t count)
{
	unsigned int reg, val;
	char *rest;
	ssize_t retval;

	reg = simple_strtoul(buf, &rest, 16);
	if (rest == buf || *rest != ' ' || reg > 0xff)
		return -EINVAL;

	retval = kstrtouint(rest + 1, 16, &val);
	if (retval)
		return retval;

	if (val > 0xff)
		return -EINVAL;

	if (fsp_reg_write_enable(psmouse, true))
		return -EIO;

	retval = fsp_reg_write(psmouse, reg, val) < 0 ? -EIO : count;

	fsp_reg_write_enable(psmouse, false);

	return count;
}