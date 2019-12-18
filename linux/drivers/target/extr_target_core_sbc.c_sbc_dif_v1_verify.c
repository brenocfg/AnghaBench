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
typedef  unsigned int u32 ;
struct t10_pi_tuple {scalar_t__ guard_tag; int /*<<< orphan*/  ref_tag; } ;
struct se_cmd {int prot_checks; scalar_t__ prot_type; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  __u16 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int TARGET_DIF_CHECK_GUARD ; 
 int TARGET_DIF_CHECK_REFTAG ; 
 scalar_t__ TARGET_DIF_TYPE1_PROT ; 
 scalar_t__ TARGET_DIF_TYPE2_PROT ; 
 int /*<<< orphan*/  TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED ; 
 int /*<<< orphan*/  TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED ; 
 unsigned int be16_to_cpu (scalar_t__) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long long,unsigned int,unsigned int) ; 

__attribute__((used)) static sense_reason_t
sbc_dif_v1_verify(struct se_cmd *cmd, struct t10_pi_tuple *sdt,
		  __u16 crc, sector_t sector, unsigned int ei_lba)
{
	__be16 csum;

	if (!(cmd->prot_checks & TARGET_DIF_CHECK_GUARD))
		goto check_ref;

	csum = cpu_to_be16(crc);

	if (sdt->guard_tag != csum) {
		pr_err("DIFv1 checksum failed on sector %llu guard tag 0x%04x"
			" csum 0x%04x\n", (unsigned long long)sector,
			be16_to_cpu(sdt->guard_tag), be16_to_cpu(csum));
		return TCM_LOGICAL_BLOCK_GUARD_CHECK_FAILED;
	}

check_ref:
	if (!(cmd->prot_checks & TARGET_DIF_CHECK_REFTAG))
		return 0;

	if (cmd->prot_type == TARGET_DIF_TYPE1_PROT &&
	    be32_to_cpu(sdt->ref_tag) != (sector & 0xffffffff)) {
		pr_err("DIFv1 Type 1 reference failed on sector: %llu tag: 0x%08x"
		       " sector MSB: 0x%08x\n", (unsigned long long)sector,
		       be32_to_cpu(sdt->ref_tag), (u32)(sector & 0xffffffff));
		return TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED;
	}

	if (cmd->prot_type == TARGET_DIF_TYPE2_PROT &&
	    be32_to_cpu(sdt->ref_tag) != ei_lba) {
		pr_err("DIFv1 Type 2 reference failed on sector: %llu tag: 0x%08x"
		       " ei_lba: 0x%08x\n", (unsigned long long)sector,
			be32_to_cpu(sdt->ref_tag), ei_lba);
		return TCM_LOGICAL_BLOCK_REF_TAG_CHECK_FAILED;
	}

	return 0;
}