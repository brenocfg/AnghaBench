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
struct hgpk_data {int xlast; int xbigj; int xsaw_secondary; int ylast; int ybigj; int ysaw_secondary; int /*<<< orphan*/  recalib_wq; } ;

/* Variables and functions */
 int abs (int) ; 
 scalar_t__ approx_half (int,int) ; 
 scalar_t__ jumpy_delay ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,...) ; 
 int recalib_delta ; 

__attribute__((used)) static int hgpk_discard_decay_hack(struct psmouse *psmouse, int x, int y)
{
	struct hgpk_data *priv = psmouse->private;
	int avx, avy;
	bool do_recal = false;

	avx = abs(x);
	avy = abs(y);

	/* discard if too big, or half that but > 4 times the prev delta */
	if (avx > recalib_delta ||
		(avx > recalib_delta / 2 && ((avx / 4) > priv->xlast))) {
		psmouse_warn(psmouse, "detected %dpx jump in x\n", x);
		priv->xbigj = avx;
	} else if (approx_half(avx, priv->xbigj)) {
		psmouse_warn(psmouse, "detected secondary %dpx jump in x\n", x);
		priv->xbigj = avx;
		priv->xsaw_secondary++;
	} else {
		if (priv->xbigj && priv->xsaw_secondary > 1)
			do_recal = true;
		priv->xbigj = 0;
		priv->xsaw_secondary = 0;
	}

	if (avy > recalib_delta ||
		(avy > recalib_delta / 2 && ((avy / 4) > priv->ylast))) {
		psmouse_warn(psmouse, "detected %dpx jump in y\n", y);
		priv->ybigj = avy;
	} else if (approx_half(avy, priv->ybigj)) {
		psmouse_warn(psmouse, "detected secondary %dpx jump in y\n", y);
		priv->ybigj = avy;
		priv->ysaw_secondary++;
	} else {
		if (priv->ybigj && priv->ysaw_secondary > 1)
			do_recal = true;
		priv->ybigj = 0;
		priv->ysaw_secondary = 0;
	}

	priv->xlast = avx;
	priv->ylast = avy;

	if (do_recal && jumpy_delay) {
		psmouse_warn(psmouse, "scheduling recalibration\n");
		psmouse_queue_work(psmouse, &priv->recalib_wq,
				msecs_to_jiffies(jumpy_delay));
	}

	return priv->xbigj || priv->ybigj;
}