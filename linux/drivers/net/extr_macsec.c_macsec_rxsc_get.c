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
struct macsec_rx_sc {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct macsec_rx_sc *macsec_rxsc_get(struct macsec_rx_sc *sc)
{
	return refcount_inc_not_zero(&sc->refcnt) ? sc : NULL;
}