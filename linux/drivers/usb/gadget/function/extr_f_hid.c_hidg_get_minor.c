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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIDG_MINORS ; 
 int /*<<< orphan*/  hidg_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int hidg_get_minor(void)
{
	int ret;

	ret = ida_simple_get(&hidg_ida, 0, 0, GFP_KERNEL);
	if (ret >= HIDG_MINORS) {
		ida_simple_remove(&hidg_ida, ret);
		ret = -ENODEV;
	}

	return ret;
}