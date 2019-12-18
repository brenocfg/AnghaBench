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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int kstrtou32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __uvcg_fill_frm_intrv(char *buf, void *priv)
{
	u32 num, **interv;
	int ret;

	ret = kstrtou32(buf, 0, &num);
	if (ret)
		return ret;

	interv = priv;
	**interv = num;
	++*interv;

	return 0;
}