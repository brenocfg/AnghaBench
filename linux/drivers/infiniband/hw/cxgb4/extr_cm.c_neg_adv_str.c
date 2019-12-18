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

/* Variables and functions */
#define  CPL_ERR_KEEPALV_NEG_ADVICE 130 
#define  CPL_ERR_PERSIST_NEG_ADVICE 129 
#define  CPL_ERR_RTX_NEG_ADVICE 128 

__attribute__((used)) static char *neg_adv_str(unsigned int status)
{
	switch (status) {
	case CPL_ERR_RTX_NEG_ADVICE:
		return "Retransmit timeout";
	case CPL_ERR_PERSIST_NEG_ADVICE:
		return "Persist timeout";
	case CPL_ERR_KEEPALV_NEG_ADVICE:
		return "Keepalive timeout";
	default:
		return "Unknown";
	}
}