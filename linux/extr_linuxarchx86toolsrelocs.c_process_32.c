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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ELF_BITS ; 
 int /*<<< orphan*/  emit_relocs (int,int) ; 
 int /*<<< orphan*/  percpu_init () ; 
 int /*<<< orphan*/  print_absolute_relocs () ; 
 int /*<<< orphan*/  print_absolute_symbols () ; 
 int /*<<< orphan*/  print_reloc_info () ; 
 int /*<<< orphan*/  read_ehdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_relocs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_shdrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_strtabs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_symtabs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regex_init (int) ; 

void process(FILE *fp, int use_real_mode, int as_text,
	     int show_absolute_syms, int show_absolute_relocs,
	     int show_reloc_info)
{
	regex_init(use_real_mode);
	read_ehdr(fp);
	read_shdrs(fp);
	read_strtabs(fp);
	read_symtabs(fp);
	read_relocs(fp);
	if (ELF_BITS == 64)
		percpu_init();
	if (show_absolute_syms) {
		print_absolute_symbols();
		return;
	}
	if (show_absolute_relocs) {
		print_absolute_relocs();
		return;
	}
	if (show_reloc_info) {
		print_reloc_info();
		return;
	}
	emit_relocs(as_text, use_real_mode);
}