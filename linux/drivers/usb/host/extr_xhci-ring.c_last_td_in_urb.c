#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xhci_td {TYPE_1__* urb; } ;
struct urb_priv {scalar_t__ num_tds_done; scalar_t__ num_tds; } ;
struct TYPE_2__ {struct urb_priv* hcpriv; } ;

/* Variables and functions */

__attribute__((used)) static bool last_td_in_urb(struct xhci_td *td)
{
	struct urb_priv *urb_priv = td->urb->hcpriv;

	return urb_priv->num_tds_done == urb_priv->num_tds;
}