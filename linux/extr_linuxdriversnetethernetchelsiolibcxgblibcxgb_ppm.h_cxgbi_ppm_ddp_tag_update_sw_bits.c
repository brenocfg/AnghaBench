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
struct cxgbi_tag_format {int free_bits; int rsvd_bits; int rsvd_mask; } ;
struct cxgbi_ppm {struct cxgbi_tag_format tformat; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cxgbi_ppm_is_ddp_tag (struct cxgbi_ppm*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static inline int cxgbi_ppm_ddp_tag_update_sw_bits(struct cxgbi_ppm *ppm,
						   u32 val, u32 orig_tag,
						   u32 *final_tag)
{
	struct cxgbi_tag_format *tformat = &ppm->tformat;
	u32 v = val >> tformat->free_bits;

	if (v) {
		pr_info("sw_bits 0x%x too large, avail bits %u.\n",
			val, tformat->free_bits);
		return -EINVAL;
	}
	if (!cxgbi_ppm_is_ddp_tag(ppm, orig_tag))
		return -EINVAL;

	*final_tag = (val << tformat->rsvd_bits) |
		     (orig_tag & ppm->tformat.rsvd_mask);
	return 0;
}