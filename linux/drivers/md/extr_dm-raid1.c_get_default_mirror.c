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
struct mirror_set {int /*<<< orphan*/  default_mirror; struct mirror* mirror; } ;
struct mirror {int dummy; } ;

/* Variables and functions */
 size_t atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mirror *get_default_mirror(struct mirror_set *ms)
{
	return &ms->mirror[atomic_read(&ms->default_mirror)];
}