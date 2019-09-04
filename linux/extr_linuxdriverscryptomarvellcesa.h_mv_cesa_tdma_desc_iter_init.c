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
struct mv_cesa_tdma_chain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mv_cesa_tdma_chain*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
mv_cesa_tdma_desc_iter_init(struct mv_cesa_tdma_chain *chain)
{
	memset(chain, 0, sizeof(*chain));
}