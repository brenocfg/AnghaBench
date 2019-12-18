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
struct ionic_lif {int dummy; } ;
struct ionic {int /*<<< orphan*/  lifbits; int /*<<< orphan*/  lifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (struct ionic_lif*) ; 
 struct ionic_lif* ionic_lif_alloc (struct ionic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ionic_lifs_alloc(struct ionic *ionic)
{
	struct ionic_lif *lif;

	INIT_LIST_HEAD(&ionic->lifs);

	/* only build the first lif, others are for later features */
	set_bit(0, ionic->lifbits);
	lif = ionic_lif_alloc(ionic, 0);

	return PTR_ERR_OR_ZERO(lif);
}