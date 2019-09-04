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
typedef  int /*<<< orphan*/  swreg ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NN_REG_LM_IDX_LO ; 
 int /*<<< orphan*/  swreg_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool swreg_lm_idx(swreg reg)
{
	return FIELD_GET(NN_REG_LM_IDX_LO, swreg_raw(reg));
}