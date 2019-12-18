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
struct super_block {int dummy; } ;

/* Variables and functions */
 int SB_NODIRATIME ; 

__attribute__((used)) static int exfat_remount(struct super_block *sb, int *flags, char *data)
{
	*flags |= SB_NODIRATIME;
	return 0;
}