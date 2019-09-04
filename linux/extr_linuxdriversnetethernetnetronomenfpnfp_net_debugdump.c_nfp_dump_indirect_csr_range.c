#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nfp_pf {int /*<<< orphan*/  cpp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dump_length; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct nfp_dumpspec_csr {TYPE_1__ cpp; int /*<<< orphan*/  register_width; TYPE_2__ tl; } ;
struct nfp_dump_state {struct nfp_dump_csr* p; } ;
struct nfp_dump_csr {void* error_offset; void* error; int /*<<< orphan*/  register_width; TYPE_1__ cpp; } ;

/* Variables and functions */
 int ALIGN8 (int) ; 
 int BITS_PER_BYTE ; 
 int /*<<< orphan*/  EINVAL ; 
 int NFP_IND_NUM_CONTEXTS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int nfp_add_tlv (int,int,struct nfp_dump_state*) ; 
 int /*<<< orphan*/  nfp_csr_spec_valid (struct nfp_dumpspec_csr*) ; 
 int nfp_dump_error_tlv (TYPE_2__*,int /*<<< orphan*/ ,struct nfp_dump_state*) ; 
 int nfp_read_all_indirect_csr_ctx (int /*<<< orphan*/ ,struct nfp_dumpspec_csr*,int,int,void*) ; 

__attribute__((used)) static int
nfp_dump_indirect_csr_range(struct nfp_pf *pf,
			    struct nfp_dumpspec_csr *spec_csr,
			    struct nfp_dump_state *dump)
{
	struct nfp_dump_csr *dump_header = dump->p;
	u32 reg_sz, header_size, total_size;
	u32 cpp_rd_addr, max_rd_addr;
	u32 reg_data_length;
	void *dest;
	int err;

	if (!nfp_csr_spec_valid(spec_csr))
		return nfp_dump_error_tlv(&spec_csr->tl, -EINVAL, dump);

	reg_sz = be32_to_cpu(spec_csr->register_width) / BITS_PER_BYTE;
	header_size = ALIGN8(sizeof(*dump_header));
	reg_data_length = be32_to_cpu(spec_csr->cpp.dump_length) *
			  NFP_IND_NUM_CONTEXTS;
	total_size = header_size + ALIGN8(reg_data_length);
	dest = dump->p + header_size;

	err = nfp_add_tlv(be32_to_cpu(spec_csr->tl.type), total_size, dump);
	if (err)
		return err;

	dump_header->cpp = spec_csr->cpp;
	dump_header->register_width = spec_csr->register_width;

	cpp_rd_addr = be32_to_cpu(spec_csr->cpp.offset);
	max_rd_addr = cpp_rd_addr + be32_to_cpu(spec_csr->cpp.dump_length);
	while (cpp_rd_addr < max_rd_addr) {
		err = nfp_read_all_indirect_csr_ctx(pf->cpp, spec_csr,
						    cpp_rd_addr, reg_sz, dest);
		if (err) {
			dump_header->error = cpu_to_be32(err);
			dump_header->error_offset = cpu_to_be32(cpp_rd_addr);
			break;
		}
		cpp_rd_addr += reg_sz;
		dest += reg_sz * NFP_IND_NUM_CONTEXTS;
	}

	return 0;
}