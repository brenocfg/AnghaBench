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
struct bq2415x_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_VENDER_CODE ; 
 int bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_get_vender_code(struct bq2415x_device *bq)
{
	int ret;

	ret = bq2415x_exec_command(bq, BQ2415X_VENDER_CODE);
	if (ret < 0)
		return 0;

	/* convert to binary */
	return (ret & 0x1) +
	       ((ret >> 1) & 0x1) * 10 +
	       ((ret >> 2) & 0x1) * 100;
}