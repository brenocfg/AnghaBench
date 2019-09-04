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
struct partition {int dummy; } ;

/* Variables and functions */
 scalar_t__ DOS_EXTENDED_PARTITION ; 
 scalar_t__ LINUX_EXTENDED_PARTITION ; 
 scalar_t__ SYS_IND (struct partition*) ; 
 scalar_t__ WIN98_EXTENDED_PARTITION ; 

__attribute__((used)) static inline int is_extended_partition(struct partition *p)
{
	return (SYS_IND(p) == DOS_EXTENDED_PARTITION ||
		SYS_IND(p) == WIN98_EXTENDED_PARTITION ||
		SYS_IND(p) == LINUX_EXTENDED_PARTITION);
}