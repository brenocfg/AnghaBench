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
struct q6v5 {scalar_t__ mpss_phys; scalar_t__ mpss_size; int /*<<< orphan*/  dev; scalar_t__ rmb_base; int /*<<< orphan*/  mpss_perm; void* mpss_region; scalar_t__ mpss_reloc; int /*<<< orphan*/  hexagon_mdt_image; } ;
struct firmware {scalar_t__ data; scalar_t__ size; } ;
struct elf32_phdr {int p_flags; scalar_t__ p_paddr; scalar_t__ p_memsz; scalar_t__ p_filesz; scalar_t__ p_offset; } ;
struct elf32_hdr {int e_phnum; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PHYS_ADDR_MAX ; 
 int QCOM_MDT_RELOCATABLE ; 
 size_t RMB_CMD_LOAD_READY ; 
 int /*<<< orphan*/  RMB_MBA_AUTH_COMPLETE ; 
 scalar_t__ RMB_MBA_COMMAND_REG ; 
 scalar_t__ RMB_PMI_CODE_LENGTH_REG ; 
 scalar_t__ RMB_PMI_CODE_START_REG ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int q6v5_mpss_init_image (struct q6v5*,struct firmware const*) ; 
 int /*<<< orphan*/  q6v5_phdr_valid (struct elf32_phdr const*) ; 
 int q6v5_rmb_mba_wait (struct q6v5*,int /*<<< orphan*/ ,int) ; 
 int q6v5_xfer_mem_ownership (struct q6v5*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int q6v5_mpss_load(struct q6v5 *qproc)
{
	const struct elf32_phdr *phdrs;
	const struct elf32_phdr *phdr;
	const struct firmware *seg_fw;
	const struct firmware *fw;
	struct elf32_hdr *ehdr;
	phys_addr_t mpss_reloc;
	phys_addr_t boot_addr;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	bool relocate = false;
	char *fw_name;
	size_t fw_name_len;
	ssize_t offset;
	size_t size = 0;
	void *ptr;
	int ret;
	int i;

	fw_name_len = strlen(qproc->hexagon_mdt_image);
	if (fw_name_len <= 4)
		return -EINVAL;

	fw_name = kstrdup(qproc->hexagon_mdt_image, GFP_KERNEL);
	if (!fw_name)
		return -ENOMEM;

	ret = request_firmware(&fw, fw_name, qproc->dev);
	if (ret < 0) {
		dev_err(qproc->dev, "unable to load %s\n", fw_name);
		goto out;
	}

	/* Initialize the RMB validator */
	writel(0, qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);

	ret = q6v5_mpss_init_image(qproc, fw);
	if (ret)
		goto release_firmware;

	ehdr = (struct elf32_hdr *)fw->data;
	phdrs = (struct elf32_phdr *)(ehdr + 1);

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!q6v5_phdr_valid(phdr))
			continue;

		if (phdr->p_flags & QCOM_MDT_RELOCATABLE)
			relocate = true;

		if (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		if (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	}

	mpss_reloc = relocate ? min_addr : qproc->mpss_phys;
	qproc->mpss_reloc = mpss_reloc;
	/* Load firmware segments */
	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!q6v5_phdr_valid(phdr))
			continue;

		offset = phdr->p_paddr - mpss_reloc;
		if (offset < 0 || offset + phdr->p_memsz > qproc->mpss_size) {
			dev_err(qproc->dev, "segment outside memory range\n");
			ret = -EINVAL;
			goto release_firmware;
		}

		ptr = qproc->mpss_region + offset;

		if (phdr->p_filesz && phdr->p_offset < fw->size) {
			/* Firmware is large enough to be non-split */
			if (phdr->p_offset + phdr->p_filesz > fw->size) {
				dev_err(qproc->dev,
					"failed to load segment %d from truncated file %s\n",
					i, fw_name);
				ret = -EINVAL;
				goto release_firmware;
			}

			memcpy(ptr, fw->data + phdr->p_offset, phdr->p_filesz);
		} else if (phdr->p_filesz) {
			/* Replace "xxx.xxx" with "xxx.bxx" */
			sprintf(fw_name + fw_name_len - 3, "b%02d", i);
			ret = request_firmware(&seg_fw, fw_name, qproc->dev);
			if (ret) {
				dev_err(qproc->dev, "failed to load %s\n", fw_name);
				goto release_firmware;
			}

			memcpy(ptr, seg_fw->data, seg_fw->size);

			release_firmware(seg_fw);
		}

		if (phdr->p_memsz > phdr->p_filesz) {
			memset(ptr + phdr->p_filesz, 0,
			       phdr->p_memsz - phdr->p_filesz);
		}
		size += phdr->p_memsz;
	}

	/* Transfer ownership of modem ddr region to q6 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, true,
				      qproc->mpss_phys, qproc->mpss_size);
	if (ret) {
		dev_err(qproc->dev,
			"assigning Q6 access to mpss memory failed: %d\n", ret);
		ret = -EAGAIN;
		goto release_firmware;
	}

	boot_addr = relocate ? qproc->mpss_phys : min_addr;
	writel(boot_addr, qproc->rmb_base + RMB_PMI_CODE_START_REG);
	writel(RMB_CMD_LOAD_READY, qproc->rmb_base + RMB_MBA_COMMAND_REG);
	writel(size, qproc->rmb_base + RMB_PMI_CODE_LENGTH_REG);

	ret = q6v5_rmb_mba_wait(qproc, RMB_MBA_AUTH_COMPLETE, 10000);
	if (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "MPSS authentication timed out\n");
	else if (ret < 0)
		dev_err(qproc->dev, "MPSS authentication failed: %d\n", ret);

release_firmware:
	release_firmware(fw);
out:
	kfree(fw_name);

	return ret < 0 ? ret : 0;
}