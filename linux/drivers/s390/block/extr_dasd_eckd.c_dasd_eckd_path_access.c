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
struct TYPE_2__ {int identifier; } ;
struct dasd_gneq {TYPE_1__ flags; } ;

/* Variables and functions */

__attribute__((used)) static unsigned char dasd_eckd_path_access(void *conf_data, int conf_len)
{
	struct dasd_gneq *gneq;
	int i, count, found;

	count = conf_len / sizeof(*gneq);
	gneq = (struct dasd_gneq *)conf_data;
	found = 0;
	for (i = 0; i < count; ++i) {
		if (gneq->flags.identifier == 2) {
			found = 1;
			break;
		}
		gneq++;
	}
	if (found)
		return ((char *)gneq)[18] & 0x07;
	else
		return 0;
}