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

/* Variables and functions */
 int sscanf (char*,char*,int*,int*,int*,int*) ; 

__attribute__((used)) static bool be_fw_ncsi_supported(char *ver)
{
	int v1[4] = {3, 102, 148, 0}; /* Min ver that supports NCSI FW */
	int v2[4];
	int i;

	if (sscanf(ver, "%d.%d.%d.%d", &v2[0], &v2[1], &v2[2], &v2[3]) != 4)
		return false;

	for (i = 0; i < 4; i++) {
		if (v1[i] < v2[i])
			return true;
		else if (v1[i] > v2[i])
			return false;
	}

	return true;
}