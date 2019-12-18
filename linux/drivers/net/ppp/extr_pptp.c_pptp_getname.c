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
struct socket {int /*<<< orphan*/  sk; } ;
struct TYPE_8__ {int /*<<< orphan*/  pptp; } ;
struct sockaddr_pppox {TYPE_4__ sa_addr; int /*<<< orphan*/  sa_protocol; int /*<<< orphan*/  sa_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_6__ {TYPE_1__ pptp; } ;
struct TYPE_7__ {TYPE_2__ proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PPPOX ; 
 int /*<<< orphan*/  PX_PROTO_PPTP ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_pppox*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* pppox_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pptp_getname(struct socket *sock, struct sockaddr *uaddr,
	int peer)
{
	int len = sizeof(struct sockaddr_pppox);
	struct sockaddr_pppox sp;

	memset(&sp.sa_addr, 0, sizeof(sp.sa_addr));

	sp.sa_family    = AF_PPPOX;
	sp.sa_protocol  = PX_PROTO_PPTP;
	sp.sa_addr.pptp = pppox_sk(sock->sk)->proto.pptp.src_addr;

	memcpy(uaddr, &sp, len);

	return len;
}