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
struct tcphdr {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct iphdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPOLEN_TIMESTAMP ; 
 int /*<<< orphan*/  cxgb4_best_aligned_mtu (unsigned short const*,unsigned short,unsigned short,int,unsigned int*) ; 
 int round_up (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
cxgb_best_mtu(const unsigned short *mtus, unsigned short mtu,
	      unsigned int *idx, int use_ts, int ipv6)
{
	unsigned short hdr_size = (ipv6 ?
				   sizeof(struct ipv6hdr) :
				   sizeof(struct iphdr)) +
				  sizeof(struct tcphdr) +
				  (use_ts ?
				   round_up(TCPOLEN_TIMESTAMP, 4) : 0);
	unsigned short data_size = mtu - hdr_size;

	cxgb4_best_aligned_mtu(mtus, hdr_size, data_size, 8, idx);
}