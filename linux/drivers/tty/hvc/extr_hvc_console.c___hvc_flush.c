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
typedef  int /*<<< orphan*/  uint32_t ;
struct hv_ops {int (* flush ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  might_sleep () ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __hvc_flush(const struct hv_ops *ops, uint32_t vtermno, bool wait)
{
	if (wait)
		might_sleep();

	if (ops->flush)
		return ops->flush(vtermno, wait);
	return 0;
}