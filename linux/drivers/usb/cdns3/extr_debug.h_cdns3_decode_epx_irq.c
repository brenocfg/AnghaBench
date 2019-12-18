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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 char* cdns3_decode_ep_irq (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline char *cdns3_decode_epx_irq(char *str,
					 char *ep_name,
					 u32 ep_sts)
{
	return cdns3_decode_ep_irq(str, ep_sts, ep_name);
}