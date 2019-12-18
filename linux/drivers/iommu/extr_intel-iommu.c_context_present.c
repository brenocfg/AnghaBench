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
struct context_entry {int dummy; } ;

/* Variables and functions */
 int __context_present (struct context_entry*) ; 
 int /*<<< orphan*/  context_copied (struct context_entry*) ; 
 scalar_t__ context_pasid_enabled (struct context_entry*) ; 

bool context_present(struct context_entry *context)
{
	return context_pasid_enabled(context) ?
	     __context_present(context) :
	     __context_present(context) && !context_copied(context);
}