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
struct brcmf_pub {int dummy; } ;
typedef  enum proto_addr_mode { ____Placeholder_proto_addr_mode } proto_addr_mode ;

/* Variables and functions */

__attribute__((used)) static void
brcmf_proto_bcdc_configure_addr_mode(struct brcmf_pub *drvr, int ifidx,
				     enum proto_addr_mode addr_mode)
{
}