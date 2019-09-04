#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int /*<<< orphan*/  has_32_hw_pid_filter; int /*<<< orphan*/  rev; TYPE_2__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int Rev_N_sig_revision_hi; int /*<<< orphan*/  Rev_N_sig_caps; } ;
struct TYPE_5__ {TYPE_1__ misc_204; } ;
typedef  TYPE_2__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  FLEXCOP_II ; 
 int /*<<< orphan*/  FLEXCOP_IIB ; 
 int /*<<< orphan*/  FLEXCOP_III ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int /*<<< orphan*/  misc_204 ; 
 TYPE_2__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 

void flexcop_determine_revision(struct flexcop_device *fc)
{
	flexcop_ibi_value v = fc->read_ibi_reg(fc,misc_204);

	switch (v.misc_204.Rev_N_sig_revision_hi) {
	case 0x2:
		deb_info("found a FlexCopII.\n");
		fc->rev = FLEXCOP_II;
		break;
	case 0x3:
		deb_info("found a FlexCopIIb.\n");
		fc->rev = FLEXCOP_IIB;
		break;
	case 0x0:
		deb_info("found a FlexCopIII.\n");
		fc->rev = FLEXCOP_III;
		break;
	default:
		err("unknown FlexCop Revision: %x. Please report this to linux-dvb@linuxtv.org.",
				v.misc_204.Rev_N_sig_revision_hi);
		break;
	}

	if ((fc->has_32_hw_pid_filter = v.misc_204.Rev_N_sig_caps))
		deb_info("this FlexCop has the additional 32 hardware pid filter.\n");
	else
		deb_info("this FlexCop has the 6 basic main hardware pid filter.\n");
	/* bus parts have to decide if hw pid filtering is used or not. */
}