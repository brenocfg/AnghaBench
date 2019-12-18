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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct brcmf_pub {int /*<<< orphan*/  bus_if; } ;

/* Variables and functions */
 int brcmf_bus_txdata (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_hdrpush (struct brcmf_pub*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int
brcmf_proto_bcdc_txdata(struct brcmf_pub *drvr, int ifidx, u8 offset,
			struct sk_buff *pktbuf)
{
	brcmf_proto_bcdc_hdrpush(drvr, ifidx, offset, pktbuf);
	return brcmf_bus_txdata(drvr->bus_if, pktbuf);
}