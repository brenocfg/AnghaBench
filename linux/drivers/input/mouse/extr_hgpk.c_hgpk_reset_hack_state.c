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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int abs_x; int abs_y; scalar_t__ ysaw_secondary; scalar_t__ xsaw_secondary; scalar_t__ ybigj; scalar_t__ xbigj; int /*<<< orphan*/  ylast; int /*<<< orphan*/  xlast; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_XY ; 
 int /*<<< orphan*/  hgpk_reset_spew_detection (struct hgpk_data*) ; 

__attribute__((used)) static void hgpk_reset_hack_state(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;

	priv->abs_x = priv->abs_y = -1;
	priv->xlast = priv->ylast = ILLEGAL_XY;
	priv->xbigj = priv->ybigj = 0;
	priv->xsaw_secondary = priv->ysaw_secondary = 0;
	hgpk_reset_spew_detection(priv);
}