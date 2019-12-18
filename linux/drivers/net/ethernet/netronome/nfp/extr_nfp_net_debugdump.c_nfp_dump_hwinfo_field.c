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
struct nfp_dump_tl {char* data; int /*<<< orphan*/  length; } ;
struct nfp_dump_state {struct nfp_dump_tl* p; } ;

/* Variables and functions */
 scalar_t__ ALIGN8 (scalar_t__) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  NFP_DUMPSPEC_TYPE_HWINFO_FIELD ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,scalar_t__) ; 
 int nfp_add_tlv (int /*<<< orphan*/ ,scalar_t__,struct nfp_dump_state*) ; 
 int nfp_dump_error_tlv (struct nfp_dump_tl*,int /*<<< orphan*/ ,struct nfp_dump_state*) ; 
 char* nfp_hwinfo_lookup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 

__attribute__((used)) static int nfp_dump_hwinfo_field(struct nfp_pf *pf, struct nfp_dump_tl *spec,
				 struct nfp_dump_state *dump)
{
	struct nfp_dump_tl *dump_header = dump->p;
	u32 tl_len, key_len, val_len;
	const char *key, *value;
	u32 total_size;
	int err;

	tl_len = be32_to_cpu(spec->length);
	key_len = strnlen(spec->data, tl_len);
	if (key_len == tl_len)
		return nfp_dump_error_tlv(spec, -EINVAL, dump);

	key = spec->data;
	value = nfp_hwinfo_lookup(pf->hwinfo, key);
	if (!value)
		return nfp_dump_error_tlv(spec, -ENOENT, dump);

	val_len = strlen(value);
	total_size = sizeof(*dump_header) + ALIGN8(key_len + val_len + 2);
	err = nfp_add_tlv(NFP_DUMPSPEC_TYPE_HWINFO_FIELD, total_size, dump);
	if (err)
		return err;

	memcpy(dump_header->data, key, key_len + 1);
	memcpy(dump_header->data + key_len + 1, value, val_len + 1);

	return 0;
}