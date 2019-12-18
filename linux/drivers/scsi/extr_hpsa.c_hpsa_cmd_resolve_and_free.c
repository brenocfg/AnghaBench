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
struct ctlr_info {int dummy; } ;
struct CommandList {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_tagged_free (struct ctlr_info*,struct CommandList*) ; 
 int /*<<< orphan*/  hpsa_cmd_resolve_events (struct ctlr_info*,struct CommandList*) ; 

__attribute__((used)) static void hpsa_cmd_resolve_and_free(struct ctlr_info *h,
				      struct CommandList *c)
{
	hpsa_cmd_resolve_events(h, c);
	cmd_tagged_free(h, c);
}