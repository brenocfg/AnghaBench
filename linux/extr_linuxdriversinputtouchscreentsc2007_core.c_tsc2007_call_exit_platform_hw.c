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
struct tsc2007_platform_data {int /*<<< orphan*/  (* exit_platform_hw ) () ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tsc2007_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void tsc2007_call_exit_platform_hw(void *data)
{
	struct device *dev = data;
	const struct tsc2007_platform_data *pdata = dev_get_platdata(dev);

	pdata->exit_platform_hw();
}