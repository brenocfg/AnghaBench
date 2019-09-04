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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct packer_context {int (* fn ) (int,int*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; scalar_t__ nr_bits; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 unsigned int min (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (unsigned int,unsigned long*) ; 
 int stub1 (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pack_bits(uint32_t index, void *value, void *context)
{
	int r;
	struct packer_context *p = context;
	unsigned bit, nr = min(64u, p->nr_bits - (index * 64));
	uint64_t word = 0;
	bool bv;

	for (bit = 0; bit < nr; bit++) {
		r = p->fn(index * 64 + bit, &bv, p->context);
		if (r)
			return r;

		if (bv)
			set_bit(bit, (unsigned long *) &word);
		else
			clear_bit(bit, (unsigned long *) &word);
	}

	*((__le64 *) value) = cpu_to_le64(word);

	return 0;
}