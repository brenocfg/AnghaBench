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
struct faulty_conf {int nfaults; scalar_t__* faults; int* modes; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 void* AllPersist ; 
 int MaxFault ; 
#define  NoPersist 131 
#define  ReadFixable 130 
#define  ReadPersistent 129 
#define  WritePersistent 128 

__attribute__((used)) static void add_sector(struct faulty_conf *conf, sector_t start, int mode)
{
	int i;
	int n = conf->nfaults;
	for (i=0; i<conf->nfaults; i++)
		if (conf->faults[i] == start) {
			switch(mode) {
			case NoPersist: conf->modes[i] = mode; return;
			case WritePersistent:
				if (conf->modes[i] == ReadPersistent ||
				    conf->modes[i] == ReadFixable)
					conf->modes[i] = AllPersist;
				else
					conf->modes[i] = WritePersistent;
				return;
			case ReadPersistent:
				if (conf->modes[i] == WritePersistent)
					conf->modes[i] = AllPersist;
				else
					conf->modes[i] = ReadPersistent;
				return;
			case ReadFixable:
				if (conf->modes[i] == WritePersistent ||
				    conf->modes[i] == ReadPersistent)
					conf->modes[i] = AllPersist;
				else
					conf->modes[i] = ReadFixable;
				return;
			}
		} else if (conf->modes[i] == NoPersist)
			n = i;

	if (n >= MaxFault)
		return;
	conf->faults[n] = start;
	conf->modes[n] = mode;
	if (conf->nfaults == n)
		conf->nfaults = n+1;
}