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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_XIF_CONFIG ; 
 int NIU_FLAGS_XMAC ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 niu_led_state_save(struct niu *np)
{
	if (np->flags & NIU_FLAGS_XMAC)
		return nr64_mac(XMAC_CONFIG);
	else
		return nr64_mac(BMAC_XIF_CONFIG);
}