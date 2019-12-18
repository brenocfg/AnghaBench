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
struct rsc_hdr {int dummy; } ;
struct entry_header {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 void const* ERR_PTR (int) ; 
 int cmd_db_get_header (char const*,struct entry_header const**,struct rsc_hdr const**) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 void const* rsc_offset (struct rsc_hdr const*,struct entry_header const*) ; 

const void *cmd_db_read_aux_data(const char *id, size_t *len)
{
	int ret;
	const struct entry_header *ent;
	const struct rsc_hdr *rsc_hdr;

	ret = cmd_db_get_header(id, &ent, &rsc_hdr);
	if (ret)
		return ERR_PTR(ret);

	if (len)
		*len = le16_to_cpu(ent->len);

	return rsc_offset(rsc_hdr, ent);
}