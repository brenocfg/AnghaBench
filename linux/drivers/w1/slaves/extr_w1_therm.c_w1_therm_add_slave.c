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
struct w1_therm_family_data {int dummy; } ;
struct w1_slave {int /*<<< orphan*/  family_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THERM_REFCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w1_therm_add_slave(struct w1_slave *sl)
{
	sl->family_data = kzalloc(sizeof(struct w1_therm_family_data),
		GFP_KERNEL);
	if (!sl->family_data)
		return -ENOMEM;
	atomic_set(THERM_REFCNT(sl->family_data), 1);
	return 0;
}