#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fw_ldst_mps_rplc {void* rplc31_0; void* rplc63_32; void* rplc95_64; void* rplc127_96; void* rplc159_128; void* rplc191_160; void* rplc223_192; void* rplc255_224; } ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP0_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP1_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP2_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP3_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP4_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP5_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP6_A ; 
 int /*<<< orphan*/  MPS_VF_RPLCT_MAP7_A ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cudbg_mps_rpl_backdoor(struct adapter *padap,
				   struct fw_ldst_mps_rplc *mps_rplc)
{
	if (is_t5(padap->params.chip)) {
		mps_rplc->rplc255_224 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP3_A));
		mps_rplc->rplc223_192 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP2_A));
		mps_rplc->rplc191_160 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP1_A));
		mps_rplc->rplc159_128 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP0_A));
	} else {
		mps_rplc->rplc255_224 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP7_A));
		mps_rplc->rplc223_192 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP6_A));
		mps_rplc->rplc191_160 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP5_A));
		mps_rplc->rplc159_128 = htonl(t4_read_reg(padap,
							  MPS_VF_RPLCT_MAP4_A));
	}
	mps_rplc->rplc127_96 = htonl(t4_read_reg(padap, MPS_VF_RPLCT_MAP3_A));
	mps_rplc->rplc95_64 = htonl(t4_read_reg(padap, MPS_VF_RPLCT_MAP2_A));
	mps_rplc->rplc63_32 = htonl(t4_read_reg(padap, MPS_VF_RPLCT_MAP1_A));
	mps_rplc->rplc31_0 = htonl(t4_read_reg(padap, MPS_VF_RPLCT_MAP0_A));
}