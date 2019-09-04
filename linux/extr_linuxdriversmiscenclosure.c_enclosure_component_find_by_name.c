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
struct enclosure_device {int components; struct enclosure_component* component; } ;
struct enclosure_component {int number; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static struct enclosure_component *
enclosure_component_find_by_name(struct enclosure_device *edev,
				const char *name)
{
	int i;
	const char *cname;
	struct enclosure_component *ecomp;

	if (!edev || !name || !name[0])
		return NULL;

	for (i = 0; i < edev->components; i++) {
		ecomp = &edev->component[i];
		cname = dev_name(&ecomp->cdev);
		if (ecomp->number != -1 &&
		    cname && cname[0] &&
		    !strcmp(cname, name))
			return ecomp;
	}

	return NULL;
}