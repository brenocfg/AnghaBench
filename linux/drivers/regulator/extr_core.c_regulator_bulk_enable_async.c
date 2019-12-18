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
struct regulator_bulk_data {int /*<<< orphan*/  consumer; int /*<<< orphan*/  ret; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regulator_bulk_enable_async(void *data, async_cookie_t cookie)
{
	struct regulator_bulk_data *bulk = data;

	bulk->ret = regulator_enable(bulk->consumer);
}