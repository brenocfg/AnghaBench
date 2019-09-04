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
struct ib_other_headers {int /*<<< orphan*/ * bth; } ;

/* Variables and functions */
 int IB_BTH_PAD_SHIFT ; 
 int OPA_16B_BTH_PAD_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 hfi1_16B_bth_get_pad(struct ib_other_headers *ohdr)
{
	return (u8)((be32_to_cpu(ohdr->bth[0]) >> IB_BTH_PAD_SHIFT) &
		   OPA_16B_BTH_PAD_MASK);
}