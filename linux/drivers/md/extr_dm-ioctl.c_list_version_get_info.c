#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vers_iter {char* end; TYPE_1__* vers; TYPE_1__* old_vers; int /*<<< orphan*/  flags; } ;
struct target_type {int /*<<< orphan*/  name; int /*<<< orphan*/ * version; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ next; int /*<<< orphan*/ * version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_BUFFER_FULL_FLAG ; 
 TYPE_1__* align_ptr (void*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void list_version_get_info(struct target_type *tt, void *param)
{
    struct vers_iter *info = param;

    /* Check space - it might have changed since the first iteration */
    if ((char *)info->vers + sizeof(tt->version) + strlen(tt->name) + 1 >
	info->end) {

	info->flags = DM_BUFFER_FULL_FLAG;
	return;
    }

    if (info->old_vers)
	info->old_vers->next = (uint32_t) ((void *)info->vers -
					   (void *)info->old_vers);
    info->vers->version[0] = tt->version[0];
    info->vers->version[1] = tt->version[1];
    info->vers->version[2] = tt->version[2];
    info->vers->next = 0;
    strcpy(info->vers->name, tt->name);

    info->old_vers = info->vers;
    info->vers = align_ptr(((void *) ++info->vers) + strlen(tt->name) + 1);
}