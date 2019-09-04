#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct psmouse {struct elantech_data* private; } ;
struct TYPE_2__ {int hw_version; } ;
struct elantech_data {TYPE_1__ info; } ;
struct elantech_attr_data {int field_offset; int reg; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned char ETP_R10_ABSOLUTE_MODE ; 
 unsigned char ETP_R11_4_BYTE_MODE ; 
 scalar_t__ elantech_write_reg (struct psmouse*,int,unsigned char) ; 
 int kstrtou8 (char const*,int,unsigned char*) ; 

__attribute__((used)) static ssize_t elantech_set_int_attr(struct psmouse *psmouse,
				     void *data, const char *buf, size_t count)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_attr_data *attr = data;
	unsigned char *reg = (unsigned char *) etd + attr->field_offset;
	unsigned char value;
	int err;

	err = kstrtou8(buf, 16, &value);
	if (err)
		return err;

	/* Do we need to preserve some bits for version 2 hardware too? */
	if (etd->info.hw_version == 1) {
		if (attr->reg == 0x10)
			/* Force absolute mode always on */
			value |= ETP_R10_ABSOLUTE_MODE;
		else if (attr->reg == 0x11)
			/* Force 4 byte mode always on */
			value |= ETP_R11_4_BYTE_MODE;
	}

	if (!attr->reg || elantech_write_reg(psmouse, attr->reg, value) == 0)
		*reg = value;

	return count;
}