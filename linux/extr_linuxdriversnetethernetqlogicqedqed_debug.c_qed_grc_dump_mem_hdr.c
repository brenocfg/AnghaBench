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
typedef  int u8 ;
typedef  int u32 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int DWORDS_TO_BYTES (int) ; 
 int qed_dump_num_param (int*,int,char*,int) ; 
 int qed_dump_section_hdr (int*,int,char*,int) ; 
 int qed_dump_str_param (int*,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static u32 qed_grc_dump_mem_hdr(struct qed_hwfn *p_hwfn,
				u32 *dump_buf,
				bool dump,
				const char *name,
				u32 addr,
				u32 len,
				u32 bit_width,
				bool packed,
				const char *mem_group,
				bool is_storm, char storm_letter)
{
	u8 num_params = 3;
	u32 offset = 0;
	char buf[64];

	if (!len)
		DP_NOTICE(p_hwfn,
			  "Unexpected GRC Dump error: dumped memory size must be non-zero\n");

	if (bit_width)
		num_params++;
	if (packed)
		num_params++;

	/* Dump section header */
	offset += qed_dump_section_hdr(dump_buf + offset,
				       dump, "grc_mem", num_params);

	if (name) {
		/* Dump name */
		if (is_storm) {
			strcpy(buf, "?STORM_");
			buf[0] = storm_letter;
			strcpy(buf + strlen(buf), name);
		} else {
			strcpy(buf, name);
		}

		offset += qed_dump_str_param(dump_buf + offset,
					     dump, "name", buf);
	} else {
		/* Dump address */
		u32 addr_in_bytes = DWORDS_TO_BYTES(addr);

		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "addr", addr_in_bytes);
	}

	/* Dump len */
	offset += qed_dump_num_param(dump_buf + offset, dump, "len", len);

	/* Dump bit width */
	if (bit_width)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "width", bit_width);

	/* Dump packed */
	if (packed)
		offset += qed_dump_num_param(dump_buf + offset,
					     dump, "packed", 1);

	/* Dump reg type */
	if (is_storm) {
		strcpy(buf, "?STORM_");
		buf[0] = storm_letter;
		strcpy(buf + strlen(buf), mem_group);
	} else {
		strcpy(buf, mem_group);
	}

	offset += qed_dump_str_param(dump_buf + offset, dump, "type", buf);

	return offset;
}