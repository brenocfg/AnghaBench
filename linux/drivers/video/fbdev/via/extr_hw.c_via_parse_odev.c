#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* device_mapping ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

u32 via_parse_odev(char *input, char **end)
{
	char *ptr = input;
	u32 odev = 0;
	bool next = true;
	int i, len;

	while (next) {
		next = false;
		for (i = 0; i < ARRAY_SIZE(device_mapping); i++) {
			len = strlen(device_mapping[i].name);
			if (!strncmp(ptr, device_mapping[i].name, len)) {
				odev |= device_mapping[i].device;
				ptr += len;
				if (*ptr == ',') {
					ptr++;
					next = true;
				}
			}
		}
	}

	*end = ptr;
	return odev;
}