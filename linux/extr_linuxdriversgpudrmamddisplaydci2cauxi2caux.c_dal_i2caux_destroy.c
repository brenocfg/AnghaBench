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
struct i2caux {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct i2caux**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  stub1 (struct i2caux**) ; 

void dal_i2caux_destroy(
	struct i2caux **i2caux)
{
	if (!i2caux || !*i2caux) {
		BREAK_TO_DEBUGGER();
		return;
	}

	(*i2caux)->funcs->destroy(i2caux);

	*i2caux = NULL;
}