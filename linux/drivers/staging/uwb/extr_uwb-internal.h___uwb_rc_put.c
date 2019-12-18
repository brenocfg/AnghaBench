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
struct uwb_rc {int /*<<< orphan*/  uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_dev_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __uwb_rc_put(struct uwb_rc *rc)
{
	if (rc)
		uwb_dev_put(&rc->uwb_dev);
}