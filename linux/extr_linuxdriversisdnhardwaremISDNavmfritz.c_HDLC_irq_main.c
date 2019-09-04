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
typedef  int u32 ;
struct fritzcard {int /*<<< orphan*/  name; } ;
struct bchannel {int dummy; } ;

/* Variables and functions */
 int HDLC_INT_MASK ; 
 int /*<<< orphan*/  HDLC_irq (struct bchannel*,int) ; 
 struct bchannel* Sel_BCS (struct fritzcard*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int read_status (struct fritzcard*,int) ; 

__attribute__((used)) static inline void
HDLC_irq_main(struct fritzcard *fc)
{
	u32 stat;
	struct bchannel *bch;

	stat = read_status(fc, 1);
	if (stat & HDLC_INT_MASK) {
		bch = Sel_BCS(fc, 1);
		if (bch)
			HDLC_irq(bch, stat);
		else
			pr_debug("%s: spurious ch1 IRQ\n", fc->name);
	}
	stat = read_status(fc, 2);
	if (stat & HDLC_INT_MASK) {
		bch = Sel_BCS(fc, 2);
		if (bch)
			HDLC_irq(bch, stat);
		else
			pr_debug("%s: spurious ch2 IRQ\n", fc->name);
	}
}