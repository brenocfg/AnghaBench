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
struct spa {int /*<<< orphan*/  spa_order; scalar_t__ spa_mem; } ;
struct ocxl_link {struct spa* spa; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct spa*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_spa(struct ocxl_link *link)
{
	struct spa *spa = link->spa;

	pr_debug("Freeing SPA for %x:%x:%x\n", link->domain, link->bus,
		link->dev);

	if (spa && spa->spa_mem) {
		free_pages((unsigned long) spa->spa_mem, spa->spa_order);
		kfree(spa);
		link->spa = NULL;
	}
}