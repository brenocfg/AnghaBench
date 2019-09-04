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
struct hfi1_pportdata {int cc_prescan; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t cc_prescan_store(struct hfi1_pportdata *ppd, const char *buf,
				size_t count)
{
	if (!memcmp(buf, "on", 2))
		ppd->cc_prescan = true;
	else if (!memcmp(buf, "off", 3))
		ppd->cc_prescan = false;

	return count;
}