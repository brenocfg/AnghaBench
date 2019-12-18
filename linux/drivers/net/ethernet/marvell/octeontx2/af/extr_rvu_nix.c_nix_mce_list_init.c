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
struct nix_mce_list {int max; scalar_t__ count; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nix_mce_list_init(struct nix_mce_list *list, int max)
{
	INIT_HLIST_HEAD(&list->head);
	list->count = 0;
	list->max = max;
}