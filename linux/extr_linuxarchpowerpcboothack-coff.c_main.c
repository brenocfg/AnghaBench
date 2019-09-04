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
struct external_scnhdr {int /*<<< orphan*/  magic; int /*<<< orphan*/  o_snbss; int /*<<< orphan*/  s_name; int /*<<< orphan*/  o_sndata; int /*<<< orphan*/  o_sntext; int /*<<< orphan*/  o_snentry; int /*<<< orphan*/  f_nscns; int /*<<< orphan*/  f_opthdr; int /*<<< orphan*/  f_magic; } ;
struct external_filehdr {int /*<<< orphan*/  magic; int /*<<< orphan*/  o_snbss; int /*<<< orphan*/  s_name; int /*<<< orphan*/  o_sndata; int /*<<< orphan*/  o_sntext; int /*<<< orphan*/  o_snentry; int /*<<< orphan*/  f_nscns; int /*<<< orphan*/  f_opthdr; int /*<<< orphan*/  f_magic; } ;
typedef  int /*<<< orphan*/  shdr ;
typedef  int /*<<< orphan*/  fhdr ;
typedef  struct external_scnhdr AOUTHDR ;

/* Variables and functions */
 int AOUT_MAGIC ; 
 int U802ROMAGIC ; 
 int U802TOCMAGIC ; 
 int U802WRMAGIC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_16be (int /*<<< orphan*/ ) ; 
 int lseek (int,long,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  put_16be (int /*<<< orphan*/ ,int) ; 
 int read (int,struct external_scnhdr*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int write (int,struct external_scnhdr*,int) ; 

int
main(int ac, char **av)
{
    int fd;
    int i, nsect;
    int aoutsz;
    struct external_filehdr fhdr;
    AOUTHDR aout;
    struct external_scnhdr shdr;

    if (ac != 2) {
	fprintf(stderr, "Usage: hack-coff coff-file\n");
	exit(1);
    }
    if ((fd = open(av[1], 2)) == -1) {
	perror(av[2]);
	exit(1);
    }
    if (read(fd, &fhdr, sizeof(fhdr)) != sizeof(fhdr))
	goto readerr;
    i = get_16be(fhdr.f_magic);
    if (i != U802TOCMAGIC && i != U802WRMAGIC && i != U802ROMAGIC) {
	fprintf(stderr, "%s: not an xcoff file\n", av[1]);
	exit(1);
    }
    aoutsz = get_16be(fhdr.f_opthdr);
    if (read(fd, &aout, aoutsz) != aoutsz)
	goto readerr;
    nsect = get_16be(fhdr.f_nscns);
    for (i = 0; i < nsect; ++i) {
	if (read(fd, &shdr, sizeof(shdr)) != sizeof(shdr))
	    goto readerr;
	if (strcmp(shdr.s_name, ".text") == 0) {
	    put_16be(aout.o_snentry, i+1);
	    put_16be(aout.o_sntext, i+1);
	} else if (strcmp(shdr.s_name, ".data") == 0) {
	    put_16be(aout.o_sndata, i+1);
	} else if (strcmp(shdr.s_name, ".bss") == 0) {
	    put_16be(aout.o_snbss, i+1);
	}
    }
    put_16be(aout.magic, AOUT_MAGIC);
    if (lseek(fd, (long) sizeof(struct external_filehdr), 0) == -1
	|| write(fd, &aout, aoutsz) != aoutsz) {
	fprintf(stderr, "%s: write error\n", av[1]);
	exit(1);
    }
    close(fd);
    exit(0);

readerr:
    fprintf(stderr, "%s: read error or file too short\n", av[1]);
    exit(1);
}