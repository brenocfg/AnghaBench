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
struct icp_qat_uof_filehdr {int num_chunks; } ;
struct icp_qat_uof_filechunkhdr {int offset; scalar_t__ checksum; int /*<<< orphan*/  size; int /*<<< orphan*/  chunk_id; } ;
struct icp_qat_uclo_objhdr {char* file_buff; scalar_t__ checksum; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICP_QAT_UOF_OBJID_LEN ; 
 struct icp_qat_uclo_objhdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qat_uclo_calc_str_checksum (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct icp_qat_uclo_objhdr *
qat_uclo_map_chunk(char *buf, struct icp_qat_uof_filehdr *file_hdr,
		   char *chunk_id)
{
	struct icp_qat_uof_filechunkhdr *file_chunk;
	struct icp_qat_uclo_objhdr *obj_hdr;
	char *chunk;
	int i;

	file_chunk = (struct icp_qat_uof_filechunkhdr *)
		(buf + sizeof(struct icp_qat_uof_filehdr));
	for (i = 0; i < file_hdr->num_chunks; i++) {
		if (!strncmp(file_chunk->chunk_id, chunk_id,
			     ICP_QAT_UOF_OBJID_LEN)) {
			chunk = buf + file_chunk->offset;
			if (file_chunk->checksum != qat_uclo_calc_str_checksum(
				chunk, file_chunk->size))
				break;
			obj_hdr = kzalloc(sizeof(*obj_hdr), GFP_KERNEL);
			if (!obj_hdr)
				break;
			obj_hdr->file_buff = chunk;
			obj_hdr->checksum = file_chunk->checksum;
			obj_hdr->size = file_chunk->size;
			return obj_hdr;
		}
		file_chunk++;
	}
	return NULL;
}