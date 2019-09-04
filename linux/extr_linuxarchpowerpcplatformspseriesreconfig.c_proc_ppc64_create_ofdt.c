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
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ofdt_fops ; 
 struct proc_dir_entry* proc_create (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_set_size (struct proc_dir_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_ppc64_create_ofdt(void)
{
	struct proc_dir_entry *ent;

	ent = proc_create("powerpc/ofdt", 0200, NULL, &ofdt_fops);
	if (ent)
		proc_set_size(ent, 0);

	return 0;
}