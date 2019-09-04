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
struct psmouse {struct elantech_data* private; } ;
struct elantech_data {int dummy; } ;
struct elantech_attr_data {int field_offset; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int elantech_read_reg (struct psmouse*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t elantech_show_int_attr(struct psmouse *psmouse, void *data,
					char *buf)
{
	struct elantech_data *etd = psmouse->private;
	struct elantech_attr_data *attr = data;
	unsigned char *reg = (unsigned char *) etd + attr->field_offset;
	int rc = 0;

	if (attr->reg)
		rc = elantech_read_reg(psmouse, attr->reg, reg);

	return sprintf(buf, "0x%02x\n", (attr->reg && rc) ? -1 : *reg);
}