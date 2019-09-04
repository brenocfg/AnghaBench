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
struct cmdline_subpart {struct cmdline_subpart* next_subpart; } ;
struct cmdline_parts {struct cmdline_subpart* subpart; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cmdline_subpart*) ; 

__attribute__((used)) static void free_subpart(struct cmdline_parts *parts)
{
	struct cmdline_subpart *subpart;

	while (parts->subpart) {
		subpart = parts->subpart;
		parts->subpart = subpart->next_subpart;
		kfree(subpart);
	}
}