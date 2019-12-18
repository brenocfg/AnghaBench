#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int u_char ;
struct TYPE_5__ {struct s_fpmc* table; } ;
struct TYPE_6__ {TYPE_1__ mc; scalar_t__ func_addr; } ;
struct TYPE_7__ {TYPE_2__ fp; } ;
struct s_smc {TYPE_3__ hw; } ;
struct TYPE_8__ {int* a; } ;
struct s_fpmc {TYPE_4__ a; scalar_t__ n; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CAM () ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_AFCMD ; 
 int /*<<< orphan*/  FM_AFCOMP0 ; 
 int /*<<< orphan*/  FM_AFCOMP1 ; 
 int /*<<< orphan*/  FM_AFCOMP2 ; 
 int /*<<< orphan*/  FM_AFMASK0 ; 
 int /*<<< orphan*/  FM_AFMASK1 ; 
 int /*<<< orphan*/  FM_AFMASK2 ; 
 int /*<<< orphan*/  FM_AFPERS ; 
 int FM_DA ; 
 int FM_IINV_CAM ; 
 int FM_IWRITE_CAM ; 
 int FM_VALID ; 
 int FPMAX_MULTICAST ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 

void mac_update_multicast(struct s_smc *smc)
{
	struct s_fpmc	*tb ;
	u_char	*fu ;
	int	i ;

	/*
	 * invalidate the CAM
	 */
	outpw(FM_A(FM_AFCMD),FM_IINV_CAM) ;

	/*
	 * set the functional address
	 */
	if (smc->hw.fp.func_addr) {
		fu = (u_char *) &smc->hw.fp.func_addr ;
		outpw(FM_A(FM_AFMASK2),0xffff) ;
		outpw(FM_A(FM_AFMASK1),(u_short) ~((fu[0] << 8) + fu[1])) ;
		outpw(FM_A(FM_AFMASK0),(u_short) ~((fu[2] << 8) + fu[3])) ;
		outpw(FM_A(FM_AFPERS),FM_VALID|FM_DA) ;
		outpw(FM_A(FM_AFCOMP2), 0xc000) ;
		outpw(FM_A(FM_AFCOMP1), 0x0000) ;
		outpw(FM_A(FM_AFCOMP0), 0x0000) ;
		outpw(FM_A(FM_AFCMD),FM_IWRITE_CAM) ;
	}

	/*
	 * set the mask and the personality register(s)
	 */
	outpw(FM_A(FM_AFMASK0),0xffff) ;
	outpw(FM_A(FM_AFMASK1),0xffff) ;
	outpw(FM_A(FM_AFMASK2),0xffff) ;
	outpw(FM_A(FM_AFPERS),FM_VALID|FM_DA) ;

	for (i = 0, tb = smc->hw.fp.mc.table; i < FPMAX_MULTICAST; i++, tb++) {
		if (tb->n) {
			CHECK_CAM() ;

			/*
			 * write the multicast address into the CAM
			 */
			outpw(FM_A(FM_AFCOMP2),
				(u_short)((tb->a.a[0]<<8)+tb->a.a[1])) ;
			outpw(FM_A(FM_AFCOMP1),
				(u_short)((tb->a.a[2]<<8)+tb->a.a[3])) ;
			outpw(FM_A(FM_AFCOMP0),
				(u_short)((tb->a.a[4]<<8)+tb->a.a[5])) ;
			outpw(FM_A(FM_AFCMD),FM_IWRITE_CAM) ;
		}
	}
}