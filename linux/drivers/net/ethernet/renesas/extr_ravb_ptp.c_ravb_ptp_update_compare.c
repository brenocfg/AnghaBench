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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int current_addend; } ;
struct ravb_private {TYPE_1__ ptp; struct net_device* ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GCCR ; 
 scalar_t__ GCCR_LPTC ; 
 int /*<<< orphan*/  GPTC ; 
 scalar_t__ ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_ptp_update_compare(struct ravb_private *priv, u32 ns)
{
	struct net_device *ndev = priv->ndev;
	/* When the comparison value (GPTC.PTCV) is in range of
	 * [x-1 to x+1] (x is the configured increment value in
	 * GTI.TIV), it may happen that a comparison match is
	 * not detected when the timer wraps around.
	 */
	u32 gti_ns_plus_1 = (priv->ptp.current_addend >> 20) + 1;
	u32 gccr;

	if (ns < gti_ns_plus_1)
		ns = gti_ns_plus_1;
	else if (ns > 0 - gti_ns_plus_1)
		ns = 0 - gti_ns_plus_1;

	gccr = ravb_read(ndev, GCCR);
	if (gccr & GCCR_LPTC)
		return -EBUSY;
	ravb_write(ndev, ns, GPTC);
	ravb_write(ndev, gccr | GCCR_LPTC, GCCR);

	return 0;
}