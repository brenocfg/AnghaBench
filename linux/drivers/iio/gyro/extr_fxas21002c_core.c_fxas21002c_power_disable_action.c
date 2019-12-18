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
struct fxas21002c_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fxas21002c_power_disable (struct fxas21002c_data*) ; 

__attribute__((used)) static void fxas21002c_power_disable_action(void *_data)
{
	struct fxas21002c_data *data = _data;

	fxas21002c_power_disable(data);
}