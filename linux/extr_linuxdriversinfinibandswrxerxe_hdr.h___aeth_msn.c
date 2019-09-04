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
typedef  int u32 ;
struct rxe_aeth {int /*<<< orphan*/  smsn; } ;

/* Variables and functions */
 int AETH_MSN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 __aeth_msn(void *arg)
{
	struct rxe_aeth *aeth = arg;

	return AETH_MSN_MASK & be32_to_cpu(aeth->smsn);
}