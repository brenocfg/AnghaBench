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
struct pnp_card {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pnp_card*) ; 
 int /*<<< orphan*/  pnp_free_card_ids (struct pnp_card*) ; 
 struct pnp_card* to_pnp_card (struct device*) ; 

__attribute__((used)) static void pnp_release_card(struct device *dmdev)
{
	struct pnp_card *card = to_pnp_card(dmdev);

	pnp_free_card_ids(card);
	kfree(card);
}