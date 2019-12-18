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
struct fsg_common {int /*<<< orphan*/ * luns; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _fsg_common_get_max_lun(struct fsg_common *common)
{
	int i = ARRAY_SIZE(common->luns) - 1;

	while (i >= 0 && !common->luns[i])
		--i;

	return i;
}