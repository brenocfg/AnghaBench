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
typedef  int /*<<< orphan*/  u32 ;
struct rproc {int dummy; } ;
struct firmware {scalar_t__ data; } ;
struct elf32_hdr {int /*<<< orphan*/  e_entry; } ;

/* Variables and functions */

u32 rproc_elf_get_boot_addr(struct rproc *rproc, const struct firmware *fw)
{
	struct elf32_hdr *ehdr  = (struct elf32_hdr *)fw->data;

	return ehdr->e_entry;
}