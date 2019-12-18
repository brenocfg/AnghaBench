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
struct se_hba {int dummy; } ;
struct se_device {int dummy; } ;
struct iblock_dev {struct se_device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iblock_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct se_device *iblock_alloc_device(struct se_hba *hba, const char *name)
{
	struct iblock_dev *ib_dev = NULL;

	ib_dev = kzalloc(sizeof(struct iblock_dev), GFP_KERNEL);
	if (!ib_dev) {
		pr_err("Unable to allocate struct iblock_dev\n");
		return NULL;
	}

	pr_debug( "IBLOCK: Allocated ib_dev for %s\n", name);

	return &ib_dev->dev;
}