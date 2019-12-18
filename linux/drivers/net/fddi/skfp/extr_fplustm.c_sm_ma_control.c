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
struct s_smc {int dummy; } ;

/* Variables and functions */
#define  MA_BEACON 132 
#define  MA_DIRECTED 131 
#define  MA_OFFLINE 130 
#define  MA_RESET 129 
#define  MA_TREQ 128 
 int /*<<< orphan*/  directed_beacon (struct s_smc*) ; 
 int /*<<< orphan*/  formac_offline (struct s_smc*) ; 
 int /*<<< orphan*/  formac_online (struct s_smc*) ; 
 int /*<<< orphan*/  init_mac (struct s_smc*,int /*<<< orphan*/ ) ; 

void sm_ma_control(struct s_smc *smc, int mode)
{
	switch(mode) {
	case MA_OFFLINE :
		/* Add to make the MAC offline in RM0_ISOLATED state */
		formac_offline(smc) ;
		break ;
	case MA_RESET :
		(void)init_mac(smc,0) ;
		break ;
	case MA_BEACON :
		formac_online(smc) ;
		break ;
	case MA_DIRECTED :
		directed_beacon(smc) ;
		break ;
	case MA_TREQ :
		/*
		 * no actions necessary, TREQ is already set
		 */
		break ;
	}
}