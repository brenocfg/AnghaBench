#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct module {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ location ;
struct TYPE_7__ {int r_offset; unsigned long r_addend; int /*<<< orphan*/  r_info; } ;
struct TYPE_6__ {size_t sh_info; int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_5__ {unsigned long st_value; } ;
typedef  TYPE_1__ Elf32_Sym ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Rela ;

/* Variables and functions */
 int ELF32_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
#define  R_MICROBLAZE_32 133 
#define  R_MICROBLAZE_32_PCREL_LO 132 
#define  R_MICROBLAZE_64 131 
#define  R_MICROBLAZE_64_NONE 130 
#define  R_MICROBLAZE_64_PCREL 129 
#define  R_MICROBLAZE_NONE 128 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int apply_relocate_add(Elf32_Shdr *sechdrs, const char *strtab,
	unsigned int symindex, unsigned int relsec, struct module *module)
{

	unsigned int i;
	Elf32_Rela *rela = (void *)sechdrs[relsec].sh_addr;
	Elf32_Sym *sym;
	unsigned long int *location;
	unsigned long int value;
#if __GNUC__ < 4
	unsigned long int old_value;
#endif

	pr_debug("Applying add relocation section %u to %u\n",
		relsec, sechdrs[relsec].sh_info);

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rela); i++) {

		location = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr +
				rela[i].r_offset;
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr +
			ELF32_R_SYM(rela[i].r_info);
		value = sym->st_value + rela[i].r_addend;

		switch (ELF32_R_TYPE(rela[i].r_info)) {

		/*
		 * Be careful! mb-gcc / mb-ld splits the relocs between the
		 * text and the reloc table. In general this means we must
		 * read the current contents of (*location), add any offset
		 * then store the result back in
		 */

		case R_MICROBLAZE_32:
#if __GNUC__ < 4
			old_value = *location;
			*location = value + old_value;

			pr_debug("R_MICROBLAZE_32 (%08lx->%08lx)\n",
				old_value, value);
#else
			*location = value;
#endif
			break;

		case R_MICROBLAZE_64:
#if __GNUC__ < 4
			/* Split relocs only required/used pre gcc4.1.1 */
			old_value = ((location[0] & 0x0000FFFF) << 16) |
					(location[1] & 0x0000FFFF);
			value += old_value;
#endif
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
#if __GNUC__ < 4
			pr_debug("R_MICROBLAZE_64 (%08lx->%08lx)\n",
				old_value, value);
#endif
			break;

		case R_MICROBLAZE_64_PCREL:
#if __GNUC__ < 4
			old_value = (location[0] & 0xFFFF) << 16 |
				(location[1] & 0xFFFF);
			value -= old_value;
#endif
			value -= (unsigned long int)(location) + 4;
			location[0] = (location[0] & 0xFFFF0000) |
					(value >> 16);
			location[1] = (location[1] & 0xFFFF0000) |
					(value & 0xFFFF);
			pr_debug("R_MICROBLAZE_64_PCREL (%08lx)\n",
				value);
			break;

		case R_MICROBLAZE_32_PCREL_LO:
			pr_debug("R_MICROBLAZE_32_PCREL_LO\n");
			break;

		case R_MICROBLAZE_64_NONE:
			pr_debug("R_MICROBLAZE_64_NONE\n");
			break;

		case R_MICROBLAZE_NONE:
			pr_debug("R_MICROBLAZE_NONE\n");
			break;

		default:
			pr_err("module %s: Unknown relocation: %u\n",
				module->name,
				ELF32_R_TYPE(rela[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;
}