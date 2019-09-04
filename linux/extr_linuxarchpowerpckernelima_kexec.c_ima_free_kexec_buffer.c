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
struct property {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int ENOENT ; 
 int do_get_kexec_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,size_t*) ; 
 int memblock_free (unsigned long,size_t) ; 
 int /*<<< orphan*/  of_chosen ; 
 struct property* of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_remove_property (int /*<<< orphan*/ ,struct property*) ; 

int ima_free_kexec_buffer(void)
{
	int ret;
	unsigned long addr;
	size_t size;
	struct property *prop;

	prop = of_find_property(of_chosen, "linux,ima-kexec-buffer", NULL);
	if (!prop)
		return -ENOENT;

	ret = do_get_kexec_buffer(prop->value, prop->length, &addr, &size);
	if (ret)
		return ret;

	ret = of_remove_property(of_chosen, prop);
	if (ret)
		return ret;

	return memblock_free(addr, size);

}