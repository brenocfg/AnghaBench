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
struct elf_shdr {int sh_type; int sh_entsize; scalar_t__ sh_addr; size_t sh_size; size_t sh_offset; } ;
typedef  int /*<<< orphan*/  Elf_Sym ;
typedef  int /*<<< orphan*/  Elf_Rela ;
typedef  int /*<<< orphan*/  Elf_Rel ;
typedef  int /*<<< orphan*/  Elf_Dyn ;

/* Variables and functions */
#define  SHT_DYNAMIC 135 
#define  SHT_HASH 134 
#define  SHT_NOBITS 133 
#define  SHT_NOTE 132 
 int SHT_NULL ; 
#define  SHT_PROGBITS 131 
#define  SHT_REL 130 
#define  SHT_RELA 129 
#define  SHT_SYMTAB 128 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static bool elf_is_shdr_sane(const struct elf_shdr *shdr, size_t buf_len)
{
	bool size_ok;

	/* SHT_NULL headers have undefined values, so we can't check them. */
	if (shdr->sh_type == SHT_NULL)
		return true;

	/* Now verify sh_entsize */
	switch (shdr->sh_type) {
	case SHT_SYMTAB:
		size_ok = shdr->sh_entsize == sizeof(Elf_Sym);
		break;
	case SHT_RELA:
		size_ok = shdr->sh_entsize == sizeof(Elf_Rela);
		break;
	case SHT_DYNAMIC:
		size_ok = shdr->sh_entsize == sizeof(Elf_Dyn);
		break;
	case SHT_REL:
		size_ok = shdr->sh_entsize == sizeof(Elf_Rel);
		break;
	case SHT_NOTE:
	case SHT_PROGBITS:
	case SHT_HASH:
	case SHT_NOBITS:
	default:
		/*
		 * This is a section whose entsize requirements
		 * I don't care about.  If I don't know about
		 * the section I can't care about it's entsize
		 * requirements.
		 */
		size_ok = true;
		break;
	}

	if (!size_ok) {
		pr_debug("ELF section with wrong entry size.\n");
		return false;
	} else if (shdr->sh_addr + shdr->sh_size < shdr->sh_addr) {
		pr_debug("ELF section address wraps around.\n");
		return false;
	}

	if (shdr->sh_type != SHT_NOBITS) {
		if (shdr->sh_offset + shdr->sh_size < shdr->sh_offset) {
			pr_debug("ELF section location wraps around.\n");
			return false;
		} else if (shdr->sh_offset + shdr->sh_size > buf_len) {
			pr_debug("ELF section not in file.\n");
			return false;
		}
	}

	return true;
}