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
struct psmouse {struct fsp_data* private; } ;
struct fsp_data {int last_reg; int /*<<< orphan*/  last_val; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fsp_attr_show_getreg(struct psmouse *psmouse,
					void *data, char *buf)
{
	struct fsp_data *pad = psmouse->private;

	return sprintf(buf, "%02x%02x\n", pad->last_reg, pad->last_val);
}