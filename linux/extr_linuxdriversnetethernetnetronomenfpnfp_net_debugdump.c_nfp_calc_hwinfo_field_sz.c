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
typedef  scalar_t__ u32 ;
struct nfp_pf {int /*<<< orphan*/  hwinfo; } ;
struct nfp_dump_tl {int /*<<< orphan*/  data; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int ALIGN8 (scalar_t__) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int nfp_dump_error_tlv_size (struct nfp_dump_tl*) ; 
 char* nfp_hwinfo_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strnlen (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nfp_calc_hwinfo_field_sz(struct nfp_pf *pf, struct nfp_dump_tl *spec)
{
	u32 tl_len, key_len;
	const char *value;

	tl_len = be32_to_cpu(spec->length);
	key_len = strnlen(spec->data, tl_len);
	if (key_len == tl_len)
		return nfp_dump_error_tlv_size(spec);

	value = nfp_hwinfo_lookup(pf->hwinfo, spec->data);
	if (!value)
		return nfp_dump_error_tlv_size(spec);

	return sizeof(struct nfp_dump_tl) + ALIGN8(key_len + strlen(value) + 2);
}