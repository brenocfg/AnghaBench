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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
struct et8ek8_reglist {int /*<<< orphan*/  regs; } ;
struct et8ek8_meta_reglist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int et8ek8_i2c_write_regs (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct et8ek8_reglist* et8ek8_reglist_find_type (struct et8ek8_meta_reglist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int et8ek8_i2c_reglist_find_write(struct i2c_client *client,
					 struct et8ek8_meta_reglist *meta,
					 u16 type)
{
	struct et8ek8_reglist *reglist;

	reglist = et8ek8_reglist_find_type(meta, type);
	if (!reglist)
		return -EINVAL;

	return et8ek8_i2c_write_regs(client, reglist->regs);
}