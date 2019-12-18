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
#define  BQ24150 140 
#define  BQ24150A 139 
#define  BQ24151 138 
#define  BQ24151A 137 
#define  BQ24152 136 
#define  BQ24153 135 
#define  BQ24153A 134 
#define  BQ24155 133 
#define  BQ24156 132 
#define  BQ24156A 131 
#define  BQ24157S 130 
#define  BQ24158 129 
 int /*<<< orphan*/  BQ2415X_REVISION ; 
#define  BQUNKNOWN 128 
 int bq2415x_detect_chip (struct bq2415x_device*) ; 
 int bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq2415x_detect_revision(struct bq2415x_device *bq)
{
	int ret = bq2415x_exec_command(bq, BQ2415X_REVISION);
	int chip = bq2415x_detect_chip(bq);

	if (ret < 0 || chip < 0)
		return -1;

	switch (chip) {
	case BQ24150:
	case BQ24150A:
	case BQ24151:
	case BQ24151A:
	case BQ24152:
		if (ret >= 0 && ret <= 3)
			return ret;
		return -1;
	case BQ24153:
	case BQ24153A:
	case BQ24156:
	case BQ24156A:
	case BQ24157S:
	case BQ24158:
		if (ret == 3)
			return 0;
		else if (ret == 1)
			return 1;
		return -1;
	case BQ24155:
		if (ret == 3)
			return 3;
		return -1;
	case BQUNKNOWN:
		return -1;
	}

	return -1;
}