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
typedef  int u8 ;
struct rxe_bth {int /*<<< orphan*/  qpn; } ;

/* Variables and functions */
 int BTH_RESV6A_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 __bth_resv6a(void *arg)
{
	struct rxe_bth *bth = arg;

	return (BTH_RESV6A_MASK & be32_to_cpu(bth->qpn)) >> 24;
}