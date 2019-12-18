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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t sbp_format_wwn(char *buf, size_t len, u64 wwn)
{
	return snprintf(buf, len, "%016llx", wwn);
}