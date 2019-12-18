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
struct socket {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EPROTONOSUPPORT ; 
#define  ISDN_P_BASE 140 
#define  ISDN_P_B_HDLC 139 
#define  ISDN_P_B_L2DSP 138 
#define  ISDN_P_B_L2DSPHDLC 137 
#define  ISDN_P_B_L2DTMF 136 
#define  ISDN_P_B_RAW 135 
#define  ISDN_P_B_X75SLP 134 
#define  ISDN_P_LAPD_NT 133 
#define  ISDN_P_LAPD_TE 132 
#define  ISDN_P_NT_E1 131 
#define  ISDN_P_NT_S0 130 
#define  ISDN_P_TE_E1 129 
#define  ISDN_P_TE_S0 128 
 int base_sock_create (struct net*,struct socket*,int,int) ; 
 int data_sock_create (struct net*,struct socket*,int,int) ; 

__attribute__((used)) static int
mISDN_sock_create(struct net *net, struct socket *sock, int proto, int kern)
{
	int err = -EPROTONOSUPPORT;

	switch (proto) {
	case ISDN_P_BASE:
		err = base_sock_create(net, sock, proto, kern);
		break;
	case ISDN_P_TE_S0:
	case ISDN_P_NT_S0:
	case ISDN_P_TE_E1:
	case ISDN_P_NT_E1:
	case ISDN_P_LAPD_TE:
	case ISDN_P_LAPD_NT:
	case ISDN_P_B_RAW:
	case ISDN_P_B_HDLC:
	case ISDN_P_B_X75SLP:
	case ISDN_P_B_L2DTMF:
	case ISDN_P_B_L2DSP:
	case ISDN_P_B_L2DSPHDLC:
		err = data_sock_create(net, sock, proto, kern);
		break;
	default:
		return err;
	}

	return err;
}