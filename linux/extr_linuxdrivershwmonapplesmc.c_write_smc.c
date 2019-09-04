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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESMC_DATA_PORT ; 
 int EIO ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 scalar_t__ send_argument (char const*) ; 
 scalar_t__ send_byte (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ send_command (int) ; 

__attribute__((used)) static int write_smc(u8 cmd, const char *key, const u8 *buffer, u8 len)
{
	int i;

	if (send_command(cmd) || send_argument(key)) {
		pr_warn("%s: write arg fail\n", key);
		return -EIO;
	}

	if (send_byte(len, APPLESMC_DATA_PORT)) {
		pr_warn("%.4s: write len fail\n", key);
		return -EIO;
	}

	for (i = 0; i < len; i++) {
		if (send_byte(buffer[i], APPLESMC_DATA_PORT)) {
			pr_warn("%s: write data fail\n", key);
			return -EIO;
		}
	}

	return 0;
}