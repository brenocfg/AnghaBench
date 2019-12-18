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
struct qib_pportdata {scalar_t__* statusp; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t show_status(struct qib_pportdata *ppd, char *buf)
{
	ssize_t ret;

	if (!ppd->statusp)
		ret = -EINVAL;
	else
		ret = scnprintf(buf, PAGE_SIZE, "0x%llx\n",
				(unsigned long long) *(ppd->statusp));
	return ret;
}