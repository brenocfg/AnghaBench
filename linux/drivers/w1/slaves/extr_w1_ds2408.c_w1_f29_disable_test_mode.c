#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct w1_slave {TYPE_1__* master; int /*<<< orphan*/  reg_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int w1_reset_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  w1_write_block (TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_f29_disable_test_mode(struct w1_slave *sl)
{
	int res;
	u8 magic[10] = {0x96, };
	u64 rn = le64_to_cpu(*((u64*)&sl->reg_num));

	memcpy(&magic[1], &rn, 8);
	magic[9] = 0x3C;

	mutex_lock(&sl->master->bus_mutex);

	res = w1_reset_bus(sl->master);
	if (res)
		goto out;
	w1_write_block(sl->master, magic, ARRAY_SIZE(magic));

	res = w1_reset_bus(sl->master);
out:
	mutex_unlock(&sl->master->bus_mutex);
	return res;
}