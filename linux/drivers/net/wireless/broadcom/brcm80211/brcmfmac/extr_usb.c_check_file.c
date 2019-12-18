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
typedef  int /*<<< orphan*/  u8 ;
struct trx_header_le {scalar_t__ magic; int /*<<< orphan*/ * offsets; int /*<<< orphan*/  flag_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRX_MAGIC ; 
 size_t TRX_OFFSETS_DLFWLEN_IDX ; 
 int TRX_UNCOMP_IMAGE ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_file(const u8 *headers)
{
	struct trx_header_le *trx;
	int actual_len = -1;

	brcmf_dbg(USB, "Enter\n");
	/* Extract trx header */
	trx = (struct trx_header_le *) headers;
	if (trx->magic != cpu_to_le32(TRX_MAGIC))
		return -1;

	headers += sizeof(struct trx_header_le);

	if (le32_to_cpu(trx->flag_version) & TRX_UNCOMP_IMAGE) {
		actual_len = le32_to_cpu(trx->offsets[TRX_OFFSETS_DLFWLEN_IDX]);
		return actual_len + sizeof(struct trx_header_le);
	}
	return -1;
}