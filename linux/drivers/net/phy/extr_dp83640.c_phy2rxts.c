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
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct rxts {int ns; int msgtype; int hash; scalar_t__ tmo; int /*<<< orphan*/  seqid; } ;
struct phy_rxts {int sec_lo; int sec_hi; int ns_lo; int ns_hi; int msgtype; int /*<<< orphan*/  seqid; } ;

/* Variables and functions */
 scalar_t__ SKB_TIMESTAMP_TIMEOUT ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void phy2rxts(struct phy_rxts *p, struct rxts *rxts)
{
	u32 sec;

	sec = p->sec_lo;
	sec |= p->sec_hi << 16;

	rxts->ns = p->ns_lo;
	rxts->ns |= (p->ns_hi & 0x3fff) << 16;
	rxts->ns += ((u64)sec) * 1000000000ULL;
	rxts->seqid = p->seqid;
	rxts->msgtype = (p->msgtype >> 12) & 0xf;
	rxts->hash = p->msgtype & 0x0fff;
	rxts->tmo = jiffies + SKB_TIMESTAMP_TIMEOUT;
}