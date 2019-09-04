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
struct target_type {int /*<<< orphan*/  name; } ;
struct dm_target_versions {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN_MASK ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void list_version_get_needed(struct target_type *tt, void *needed_param)
{
    size_t *needed = needed_param;

    *needed += sizeof(struct dm_target_versions);
    *needed += strlen(tt->name);
    *needed += ALIGN_MASK;
}