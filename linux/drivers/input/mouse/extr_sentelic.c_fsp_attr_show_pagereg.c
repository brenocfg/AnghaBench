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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ fsp_page_reg_read (struct psmouse*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t fsp_attr_show_pagereg(struct psmouse *psmouse,
					void *data, char *buf)
{
	int val = 0;

	if (fsp_page_reg_read(psmouse, &val))
		return -EIO;

	return sprintf(buf, "%02x\n", val);
}