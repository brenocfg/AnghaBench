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
struct pscsi_dev_virt {struct se_device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pscsi_dev_virt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct pscsi_dev_virt*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct se_device *pscsi_alloc_device(struct se_hba *hba,
		const char *name)
{
	struct pscsi_dev_virt *pdv;

	pdv = kzalloc(sizeof(struct pscsi_dev_virt), GFP_KERNEL);
	if (!pdv) {
		pr_err("Unable to allocate memory for struct pscsi_dev_virt\n");
		return NULL;
	}

	pr_debug("PSCSI: Allocated pdv: %p for %s\n", pdv, name);
	return &pdv->dev;
}