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
typedef  int u_long ;
struct socket_data {int /*<<< orphan*/  mem_db; } ;
struct pcmcia_socket {int map_size; int /*<<< orphan*/  dev; struct socket_data* resource_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  do_validate_mem (struct pcmcia_socket*,int,int,int (*) (struct pcmcia_socket*,struct resource*,unsigned int*)) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  sub_interval (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int do_mem_probe(struct pcmcia_socket *s, u_long base, u_long num,
			int validate (struct pcmcia_socket *s,
				      struct resource *res,
				      unsigned int *value),
			int fallback (struct pcmcia_socket *s,
				      struct resource *res,
				      unsigned int *value))
{
	struct socket_data *s_data = s->resource_data;
	u_long i, j, bad, fail, step;

	dev_info(&s->dev, "cs: memory probe 0x%06lx-0x%06lx:",
		 base, base+num-1);
	bad = fail = 0;
	step = (num < 0x20000) ? 0x2000 : ((num>>4) & ~0x1fff);
	/* don't allow too large steps */
	if (step > 0x800000)
		step = 0x800000;
	/* cis_readable wants to map 2x map_size */
	if (step < 2 * s->map_size)
		step = 2 * s->map_size;
	for (i = j = base; i < base+num; i = j + step) {
		if (!fail) {
			for (j = i; j < base+num; j += step) {
				if (!do_validate_mem(s, j, step, validate))
					break;
			}
			fail = ((i == base) && (j == base+num));
		}
		if ((fail) && (fallback)) {
			for (j = i; j < base+num; j += step)
				if (!do_validate_mem(s, j, step, fallback))
					break;
		}
		if (i != j) {
			if (!bad)
				pr_cont(" excluding");
			pr_cont(" %#05lx-%#05lx", i, j-1);
			sub_interval(&s_data->mem_db, i, j-i);
			bad += j-i;
		}
	}
	pr_cont("%s\n", !bad ? " clean" : "");
	return num - bad;
}