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
struct entry_alloc {int begin; int /*<<< orphan*/  es; } ;
struct entry {int dummy; } ;

/* Variables and functions */
 int to_index (int /*<<< orphan*/ ,struct entry*) ; 

__attribute__((used)) static unsigned get_index(struct entry_alloc *ea, struct entry *e)
{
	return to_index(ea->es, e) - ea->begin;
}