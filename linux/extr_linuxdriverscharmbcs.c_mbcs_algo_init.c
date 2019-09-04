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
struct algoblock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct algoblock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mbcs_algo_init(struct algoblock *algo_soft)
{
	memset(algo_soft, 0, sizeof(struct algoblock));
}