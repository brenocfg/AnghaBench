#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_2__ {scalar_t__* e_ident; int /*<<< orphan*/  e_flags; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; } ;
typedef  int Elf32_Word ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 int EF_ARM_ABI_FLOAT_HARD ; 
 int EF_ARM_ABI_FLOAT_SOFT ; 
 int /*<<< orphan*/  EF_ARM_EABI_VER5 ; 
 int /*<<< orphan*/  EF_ARM_EABI_VERSION (int) ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 scalar_t__ ELFCLASS32 ; 
 int /*<<< orphan*/  ELFMAG ; 
 scalar_t__ EM_ARM ; 
 scalar_t__ ET_DYN ; 
 int EXIT_SUCCESS ; 
 scalar_t__ HOST_ORDER ; 
 void const* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  SELFMAG ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 char* argv0 ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fail (char*,...) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ftruncate (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 void* mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msync (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int,...) ; 
 char const* outfile ; 
 scalar_t__ read_elf_half (int /*<<< orphan*/ ,int) ; 
 int read_elf_word (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_elf_word (int,int /*<<< orphan*/ *,int) ; 

int main(int argc, char **argv)
{
	const Elf32_Ehdr *inhdr;
	bool clear_soft_float;
	const char *infile;
	Elf32_Word e_flags;
	const void *inbuf;
	struct stat stat;
	void *outbuf;
	bool swap;
	int outfd;
	int infd;

	atexit(cleanup);
	argv0 = argv[0];

	if (argc != 3)
		fail("Usage: %s [infile] [outfile]\n", argv[0]);

	infile = argv[1];
	outfile = argv[2];

	infd = open(infile, O_RDONLY);
	if (infd < 0)
		fail("Cannot open %s: %s\n", infile, strerror(errno));

	if (fstat(infd, &stat) != 0)
		fail("Failed stat for %s: %s\n", infile, strerror(errno));

	inbuf = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, infd, 0);
	if (inbuf == MAP_FAILED)
		fail("Failed to map %s: %s\n", infile, strerror(errno));

	close(infd);

	inhdr = inbuf;

	if (memcmp(&inhdr->e_ident, ELFMAG, SELFMAG) != 0)
		fail("Not an ELF file\n");

	if (inhdr->e_ident[EI_CLASS] != ELFCLASS32)
		fail("Unsupported ELF class\n");

	swap = inhdr->e_ident[EI_DATA] != HOST_ORDER;

	if (read_elf_half(inhdr->e_type, swap) != ET_DYN)
		fail("Not a shared object\n");

	if (read_elf_half(inhdr->e_machine, swap) != EM_ARM)
		fail("Unsupported architecture %#x\n", inhdr->e_machine);

	e_flags = read_elf_word(inhdr->e_flags, swap);

	if (EF_ARM_EABI_VERSION(e_flags) != EF_ARM_EABI_VER5) {
		fail("Unsupported EABI version %#x\n",
		     EF_ARM_EABI_VERSION(e_flags));
	}

	if (e_flags & EF_ARM_ABI_FLOAT_HARD)
		fail("Unexpected hard-float flag set in e_flags\n");

	clear_soft_float = !!(e_flags & EF_ARM_ABI_FLOAT_SOFT);

	outfd = open(outfile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (outfd < 0)
		fail("Cannot open %s: %s\n", outfile, strerror(errno));

	if (ftruncate(outfd, stat.st_size) != 0)
		fail("Cannot truncate %s: %s\n", outfile, strerror(errno));

	outbuf = mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		      outfd, 0);
	if (outbuf == MAP_FAILED)
		fail("Failed to map %s: %s\n", outfile, strerror(errno));

	close(outfd);

	memcpy(outbuf, inbuf, stat.st_size);

	if (clear_soft_float) {
		Elf32_Ehdr *outhdr;

		outhdr = outbuf;
		e_flags &= ~EF_ARM_ABI_FLOAT_SOFT;
		write_elf_word(e_flags, &outhdr->e_flags, swap);
	}

	if (msync(outbuf, stat.st_size, MS_SYNC) != 0)
		fail("Failed to sync %s: %s\n", outfile, strerror(errno));

	return EXIT_SUCCESS;
}