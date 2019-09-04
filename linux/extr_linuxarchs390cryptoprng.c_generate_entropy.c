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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  CPACF_KIMD_SHA_512 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PRNG_GEN_ENTROPY_FAILED ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpacf_kimd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_tod_clock_fast () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prng_errorflag ; 

__attribute__((used)) static int generate_entropy(u8 *ebuf, size_t nbytes)
{
	int n, ret = 0;
	u8 *pg, *h, hash[64];

	/* allocate 2 pages */
	pg = (u8 *) __get_free_pages(GFP_KERNEL, 1);
	if (!pg) {
		prng_errorflag = PRNG_GEN_ENTROPY_FAILED;
		return -ENOMEM;
	}

	while (nbytes) {
		/* fill pages with urandom bytes */
		get_random_bytes(pg, 2*PAGE_SIZE);
		/* exor pages with 1024 stckf values */
		for (n = 0; n < 2 * PAGE_SIZE / sizeof(u64); n++) {
			u64 *p = ((u64 *)pg) + n;
			*p ^= get_tod_clock_fast();
		}
		n = (nbytes < sizeof(hash)) ? nbytes : sizeof(hash);
		if (n < sizeof(hash))
			h = hash;
		else
			h = ebuf;
		/* hash over the filled pages */
		cpacf_kimd(CPACF_KIMD_SHA_512, h, pg, 2*PAGE_SIZE);
		if (n < sizeof(hash))
			memcpy(ebuf, hash, n);
		ret += n;
		ebuf += n;
		nbytes -= n;
	}

	free_pages((unsigned long)pg, 1);
	return ret;
}