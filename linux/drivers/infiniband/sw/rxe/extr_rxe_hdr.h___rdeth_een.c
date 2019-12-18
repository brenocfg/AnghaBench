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
struct rxe_rdeth {int /*<<< orphan*/  een; } ;

/* Variables and functions */
 int RDETH_EEN_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 __rdeth_een(void *arg)
{
	struct rxe_rdeth *rdeth = arg;

	return RDETH_EEN_MASK & be32_to_cpu(rdeth->een);
}