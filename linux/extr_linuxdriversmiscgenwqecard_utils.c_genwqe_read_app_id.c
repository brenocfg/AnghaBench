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
typedef  int u32 ;
struct genwqe_dev {int /*<<< orphan*/  app_unitcfg; } ;

/* Variables and functions */
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 

int genwqe_read_app_id(struct genwqe_dev *cd, char *app_name, int len)
{
	int i, j;
	u32 app_id = (u32)cd->app_unitcfg;

	memset(app_name, 0, len);
	for (i = 0, j = 0; j < min(len, 4); j++) {
		char ch = (char)((app_id >> (24 - j*8)) & 0xff);

		if (ch == ' ')
			continue;
		app_name[i++] = isprint(ch) ? ch : 'X';
	}
	return i;
}