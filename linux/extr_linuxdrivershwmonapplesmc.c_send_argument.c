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
 int /*<<< orphan*/  APPLESMC_DATA_PORT ; 
 int EIO ; 
 scalar_t__ send_byte (char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_argument(const char *key)
{
	int i;

	for (i = 0; i < 4; i++)
		if (send_byte(key[i], APPLESMC_DATA_PORT))
			return -EIO;
	return 0;
}