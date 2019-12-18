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
struct firmware {scalar_t__ data; scalar_t__ size; } ;
struct elf32_phdr {int p_flags; scalar_t__ p_paddr; size_t p_memsz; size_t p_filesz; scalar_t__ p_offset; } ;
struct elf32_hdr {int e_phnum; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ PHYS_ADDR_MAX ; 
 int PTR_ERR (void*) ; 
 int QCOM_MDT_RELOCATABLE ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdt_phdr_valid (struct elf32_phdr const*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* qcom_mdt_read_metadata (struct firmware const*,size_t*) ; 
 int qcom_scm_pas_init_image (int,void*,size_t) ; 
 int qcom_scm_pas_mem_setup (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware_into_buf (struct firmware const**,char*,struct device*,void*,size_t) ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int __qcom_mdt_load(struct device *dev, const struct firmware *fw,
			   const char *firmware, int pas_id, void *mem_region,
			   phys_addr_t mem_phys, size_t mem_size,
			   phys_addr_t *reloc_base, bool pas_init)
{
	const struct elf32_phdr *phdrs;
	const struct elf32_phdr *phdr;
	const struct elf32_hdr *ehdr;
	const struct firmware *seg_fw;
	phys_addr_t mem_reloc;
	phys_addr_t min_addr = PHYS_ADDR_MAX;
	phys_addr_t max_addr = 0;
	size_t metadata_len;
	size_t fw_name_len;
	ssize_t offset;
	void *metadata;
	char *fw_name;
	bool relocate = false;
	void *ptr;
	int ret = 0;
	int i;

	if (!fw || !mem_region || !mem_phys || !mem_size)
		return -EINVAL;

	ehdr = (struct elf32_hdr *)fw->data;
	phdrs = (struct elf32_phdr *)(ehdr + 1);

	fw_name_len = strlen(firmware);
	if (fw_name_len <= 4)
		return -EINVAL;

	fw_name = kstrdup(firmware, GFP_KERNEL);
	if (!fw_name)
		return -ENOMEM;

	if (pas_init) {
		metadata = qcom_mdt_read_metadata(fw, &metadata_len);
		if (IS_ERR(metadata)) {
			ret = PTR_ERR(metadata);
			goto out;
		}

		ret = qcom_scm_pas_init_image(pas_id, metadata, metadata_len);

		kfree(metadata);
		if (ret) {
			dev_err(dev, "invalid firmware metadata\n");
			goto out;
		}
	}

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!mdt_phdr_valid(phdr))
			continue;

		if (phdr->p_flags & QCOM_MDT_RELOCATABLE)
			relocate = true;

		if (phdr->p_paddr < min_addr)
			min_addr = phdr->p_paddr;

		if (phdr->p_paddr + phdr->p_memsz > max_addr)
			max_addr = ALIGN(phdr->p_paddr + phdr->p_memsz, SZ_4K);
	}

	if (relocate) {
		if (pas_init) {
			ret = qcom_scm_pas_mem_setup(pas_id, mem_phys,
						     max_addr - min_addr);
			if (ret) {
				dev_err(dev, "unable to setup relocation\n");
				goto out;
			}
		}

		/*
		 * The image is relocatable, so offset each segment based on
		 * the lowest segment address.
		 */
		mem_reloc = min_addr;
	} else {
		/*
		 * Image is not relocatable, so offset each segment based on
		 * the allocated physical chunk of memory.
		 */
		mem_reloc = mem_phys;
	}

	for (i = 0; i < ehdr->e_phnum; i++) {
		phdr = &phdrs[i];

		if (!mdt_phdr_valid(phdr))
			continue;

		offset = phdr->p_paddr - mem_reloc;
		if (offset < 0 || offset + phdr->p_memsz > mem_size) {
			dev_err(dev, "segment outside memory range\n");
			ret = -EINVAL;
			break;
		}

		ptr = mem_region + offset;

		if (phdr->p_filesz && phdr->p_offset < fw->size) {
			/* Firmware is large enough to be non-split */
			if (phdr->p_offset + phdr->p_filesz > fw->size) {
				dev_err(dev,
					"failed to load segment %d from truncated file %s\n",
					i, firmware);
				ret = -EINVAL;
				break;
			}

			memcpy(ptr, fw->data + phdr->p_offset, phdr->p_filesz);
		} else if (phdr->p_filesz) {
			/* Firmware not large enough, load split-out segments */
			sprintf(fw_name + fw_name_len - 3, "b%02d", i);
			ret = request_firmware_into_buf(&seg_fw, fw_name, dev,
							ptr, phdr->p_filesz);
			if (ret) {
				dev_err(dev, "failed to load %s\n", fw_name);
				break;
			}

			release_firmware(seg_fw);
		}

		if (phdr->p_memsz > phdr->p_filesz)
			memset(ptr + phdr->p_filesz, 0, phdr->p_memsz - phdr->p_filesz);
	}

	if (reloc_base)
		*reloc_base = mem_reloc;

out:
	kfree(fw_name);

	return ret;
}