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
struct rproc {struct q6v5* priv; } ;
struct q6v5 {int /*<<< orphan*/  dump_complete_mask; int /*<<< orphan*/  hexagon_mdt_image; int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ data; } ;
struct elf32_phdr {int /*<<< orphan*/  p_memsz; int /*<<< orphan*/  p_paddr; } ;
struct elf32_hdr {unsigned long e_phnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_phdr_valid (struct elf32_phdr const*) ; 
 int /*<<< orphan*/  qcom_q6v5_dump_segment ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rproc_coredump_add_custom_segment (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int qcom_q6v5_register_dump_segments(struct rproc *rproc,
					    const struct firmware *mba_fw)
{
	const struct firmware *fw;
	const struct elf32_phdr *phdrs;
	const struct elf32_phdr *phdr;
	const struct elf32_hdr *ehdr;
	struct q6v5 *qproc = rproc->priv;
	unsigned long i;
	int ret;

	ret = request_firmware(&fw, qproc->hexagon_mdt_image, qproc->dev);
	if (ret < 0) {
		dev_err(qproc->dev, "unable to load %s\n",
			qproc->hexagon_mdt_image);
		return ret;
	}

	ehdr = (struct elf32_hdr *)fw->data;
	phdrs = (struct elf32_phdr *)(ehdr + 1);
	qproc->dump_complete_mask = 0;

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!q6v5_phdr_valid(phdr))
			continue;

		ret = rproc_coredump_add_custom_segment(rproc, phdr->p_paddr,
							phdr->p_memsz,
							qcom_q6v5_dump_segment,
							(void *)i);
		if (ret)
			break;

		qproc->dump_complete_mask |= BIT(i);
	}

	release_firmware(fw);
	return ret;
}