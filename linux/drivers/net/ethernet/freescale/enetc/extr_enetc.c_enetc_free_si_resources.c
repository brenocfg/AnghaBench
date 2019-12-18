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
struct enetc_si {int /*<<< orphan*/  cbd_ring; int /*<<< orphan*/  hw; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  cls_rules; int /*<<< orphan*/  dev; struct enetc_si* si; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_clear_cbdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_free_cbdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void enetc_free_si_resources(struct enetc_ndev_priv *priv)
{
	struct enetc_si *si = priv->si;

	enetc_clear_cbdr(&si->hw);
	enetc_free_cbdr(priv->dev, &si->cbd_ring);

	kfree(priv->cls_rules);
}