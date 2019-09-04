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
struct rand_data {int disable_unbias; int data; unsigned int osr; scalar_t__ stir; scalar_t__ stuck; } ;
typedef  int __u64 ;

/* Variables and functions */
 unsigned int DATA_SIZE_BITS ; 
 int jent_measure_jitter (struct rand_data*) ; 
 int jent_rol64 (int,int) ; 
 int /*<<< orphan*/  jent_stir_pool (struct rand_data*) ; 
 int jent_unbiased_bit (struct rand_data*) ; 

__attribute__((used)) static void jent_gen_entropy(struct rand_data *ec)
{
	unsigned int k = 0;

	/* priming of the ->prev_time value */
	jent_measure_jitter(ec);

	while (1) {
		__u64 data = 0;

		if (ec->disable_unbias == 1)
			data = jent_measure_jitter(ec);
		else
			data = jent_unbiased_bit(ec);

		/* enforcement of the jent_stuck test */
		if (ec->stuck) {
			/*
			 * We only mix in the bit considered not appropriate
			 * without the LSFR. The reason is that if we apply
			 * the LSFR and we do not rotate, the 2nd bit with LSFR
			 * will cancel out the first LSFR application on the
			 * bad bit.
			 *
			 * And we do not rotate as we apply the next bit to the
			 * current bit location again.
			 */
			ec->data ^= data;
			ec->stuck = 0;
			continue;
		}

		/*
		 * Fibonacci LSFR with polynom of
		 *  x^64 + x^61 + x^56 + x^31 + x^28 + x^23 + 1 which is
		 *  primitive according to
		 *   http://poincare.matf.bg.ac.rs/~ezivkovm/publications/primpol1.pdf
		 * (the shift values are the polynom values minus one
		 * due to counting bits from 0 to 63). As the current
		 * position is always the LSB, the polynom only needs
		 * to shift data in from the left without wrap.
		 */
		ec->data ^= data;
		ec->data ^= ((ec->data >> 63) & 1);
		ec->data ^= ((ec->data >> 60) & 1);
		ec->data ^= ((ec->data >> 55) & 1);
		ec->data ^= ((ec->data >> 30) & 1);
		ec->data ^= ((ec->data >> 27) & 1);
		ec->data ^= ((ec->data >> 22) & 1);
		ec->data = jent_rol64(ec->data, 1);

		/*
		 * We multiply the loop value with ->osr to obtain the
		 * oversampling rate requested by the caller
		 */
		if (++k >= (DATA_SIZE_BITS * ec->osr))
			break;
	}
	if (ec->stir)
		jent_stir_pool(ec);
}