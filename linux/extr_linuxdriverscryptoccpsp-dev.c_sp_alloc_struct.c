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
struct sp_device {int ord; int /*<<< orphan*/  name; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SP_MAX_NAME_LEN ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct sp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sp_ordinal ; 

struct sp_device *sp_alloc_struct(struct device *dev)
{
	struct sp_device *sp;

	sp = devm_kzalloc(dev, sizeof(*sp), GFP_KERNEL);
	if (!sp)
		return NULL;

	sp->dev = dev;
	sp->ord = atomic_inc_return(&sp_ordinal);
	snprintf(sp->name, SP_MAX_NAME_LEN, "sp-%u", sp->ord);

	return sp;
}