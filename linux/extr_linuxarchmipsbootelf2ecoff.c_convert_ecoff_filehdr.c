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
struct filehdr {void* f_flags; void* f_opthdr; void* f_nsyms; void* f_symptr; void* f_timdat; void* f_nscns; void* f_magic; } ;

/* Variables and functions */
 void* swab16 (void*) ; 
 void* swab32 (void*) ; 

__attribute__((used)) static void convert_ecoff_filehdr(struct filehdr *f)
{
	f->f_magic = swab16(f->f_magic);
	f->f_nscns = swab16(f->f_nscns);
	f->f_timdat = swab32(f->f_timdat);
	f->f_symptr = swab32(f->f_symptr);
	f->f_nsyms = swab32(f->f_nsyms);
	f->f_opthdr = swab16(f->f_opthdr);
	f->f_flags = swab16(f->f_flags);
}