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
typedef  enum nfp_bpf_reg_type { ____Placeholder_nfp_bpf_reg_type } nfp_bpf_reg_type ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NN_REG_TYPE ; 
 int /*<<< orphan*/  swreg_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum nfp_bpf_reg_type swreg_type(swreg reg)
{
	return FIELD_GET(NN_REG_TYPE, swreg_raw(reg));
}