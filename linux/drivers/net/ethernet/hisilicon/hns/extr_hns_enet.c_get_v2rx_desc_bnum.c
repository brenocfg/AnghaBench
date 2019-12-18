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
 int /*<<< orphan*/  HNS_RXD_BUFNUM_M ; 
 int /*<<< orphan*/  HNS_RXD_BUFNUM_S ; 
 int hnae_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_v2rx_desc_bnum(u32 bnum_flag, int *out_bnum)
{
	*out_bnum = hnae_get_field(bnum_flag,
				   HNS_RXD_BUFNUM_M, HNS_RXD_BUFNUM_S) + 1;
}