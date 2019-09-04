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
struct rxe_deth {int /*<<< orphan*/  qkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __deth_set_qkey(void *arg, u32 qkey)
{
	struct rxe_deth *deth = arg;

	deth->qkey = cpu_to_be32(qkey);
}