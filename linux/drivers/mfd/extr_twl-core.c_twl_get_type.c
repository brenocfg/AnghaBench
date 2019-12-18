#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  twl_idcode; } ;

/* Variables and functions */
 int TWL_SIL_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* twl_priv ; 

int twl_get_type(void)
{
	return TWL_SIL_TYPE(twl_priv->twl_idcode);
}