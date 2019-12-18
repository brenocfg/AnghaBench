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
struct pm860x_battery_info {int dummy; } ;
struct ccnt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCNT_NEG1 ; 
 int /*<<< orphan*/  CCNT_NEG2 ; 
 int /*<<< orphan*/  CCNT_POS1 ; 
 int /*<<< orphan*/  CCNT_POS2 ; 
 int /*<<< orphan*/  CCNT_SNEG ; 
 int /*<<< orphan*/  CCNT_SPOS ; 
 int /*<<< orphan*/  memset (struct ccnt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_ccnt (struct pm860x_battery_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int clear_ccnt(struct pm860x_battery_info *info, struct ccnt *ccnt)
{
	int data;

	memset(ccnt, 0, sizeof(*ccnt));
	/* read to clear ccnt */
	read_ccnt(info, CCNT_POS1, &data);
	read_ccnt(info, CCNT_POS2, &data);
	read_ccnt(info, CCNT_NEG1, &data);
	read_ccnt(info, CCNT_NEG2, &data);
	read_ccnt(info, CCNT_SPOS, &data);
	read_ccnt(info, CCNT_SNEG, &data);
	return 0;
}