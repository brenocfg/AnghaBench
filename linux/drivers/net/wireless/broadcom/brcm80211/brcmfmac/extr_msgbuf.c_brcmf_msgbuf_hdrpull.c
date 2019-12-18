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
struct sk_buff {int dummy; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int brcmf_msgbuf_hdrpull(struct brcmf_pub *drvr, bool do_fws,
				struct sk_buff *skb, struct brcmf_if **ifp)
{
	return -ENODEV;
}