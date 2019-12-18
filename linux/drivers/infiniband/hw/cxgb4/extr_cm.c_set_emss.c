#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct tcphdr {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_9__ {scalar_t__ ss_family; } ;
struct TYPE_10__ {TYPE_4__ remote_addr; TYPE_3__* dev; } ;
struct c4iw_ep {int emss; int mss; TYPE_5__ com; } ;
struct TYPE_6__ {int* mtus; } ;
struct TYPE_7__ {TYPE_1__ lldi; } ;
struct TYPE_8__ {TYPE_2__ rdev; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  TCPOLEN_TIMESTAMP ; 
 size_t TCPOPT_MSS_G (int /*<<< orphan*/ ) ; 
 scalar_t__ TCPOPT_TSTAMP_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,int,int) ; 
 scalar_t__ round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_emss(struct c4iw_ep *ep, u16 opt)
{
	ep->emss = ep->com.dev->rdev.lldi.mtus[TCPOPT_MSS_G(opt)] -
		   ((AF_INET == ep->com.remote_addr.ss_family) ?
		    sizeof(struct iphdr) : sizeof(struct ipv6hdr)) -
		   sizeof(struct tcphdr);
	ep->mss = ep->emss;
	if (TCPOPT_TSTAMP_G(opt))
		ep->emss -= round_up(TCPOLEN_TIMESTAMP, 4);
	if (ep->emss < 128)
		ep->emss = 128;
	if (ep->emss & 7)
		pr_debug("Warning: misaligned mtu idx %u mss %u emss=%u\n",
			 TCPOPT_MSS_G(opt), ep->mss, ep->emss);
	pr_debug("mss_idx %u mss %u emss=%u\n", TCPOPT_MSS_G(opt), ep->mss,
		 ep->emss);
}