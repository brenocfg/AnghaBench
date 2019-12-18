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
struct t10_pi_tuple {scalar_t__ guard_tag; int /*<<< orphan*/  ref_tag; } ;
typedef  int sector_t ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 scalar_t__ T10_PI_TYPE1_PROTECTION ; 
 scalar_t__ T10_PI_TYPE2_PROTECTION ; 
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ dif_compute_csum (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,...) ; 
 scalar_t__ sdebug_dif ; 
 int /*<<< orphan*/  sdebug_sector_size ; 

__attribute__((used)) static int dif_verify(struct t10_pi_tuple *sdt, const void *data,
		      sector_t sector, u32 ei_lba)
{
	__be16 csum = dif_compute_csum(data, sdebug_sector_size);

	if (sdt->guard_tag != csum) {
		pr_err("GUARD check failed on sector %lu rcvd 0x%04x, data 0x%04x\n",
			(unsigned long)sector,
			be16_to_cpu(sdt->guard_tag),
			be16_to_cpu(csum));
		return 0x01;
	}
	if (sdebug_dif == T10_PI_TYPE1_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != (sector & 0xffffffff)) {
		pr_err("REF check failed on sector %lu\n",
			(unsigned long)sector);
		return 0x03;
	}
	if (sdebug_dif == T10_PI_TYPE2_PROTECTION &&
	    be32_to_cpu(sdt->ref_tag) != ei_lba) {
		pr_err("REF check failed on sector %lu\n",
			(unsigned long)sector);
		return 0x03;
	}
	return 0;
}