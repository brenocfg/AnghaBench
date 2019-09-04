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
typedef  int u32 ;
struct qcom_rng {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PRNG_DATA_OUT ; 
 scalar_t__ PRNG_STATUS ; 
 int PRNG_STATUS_DATA_AVAIL ; 
 unsigned int WORD_SZ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,unsigned int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int qcom_rng_read(struct qcom_rng *rng, u8 *data, unsigned int max)
{
	unsigned int currsize = 0;
	u32 val;

	/* read random data from hardware */
	do {
		val = readl_relaxed(rng->base + PRNG_STATUS);
		if (!(val & PRNG_STATUS_DATA_AVAIL))
			break;

		val = readl_relaxed(rng->base + PRNG_DATA_OUT);
		if (!val)
			break;

		if ((max - currsize) >= WORD_SZ) {
			memcpy(data, &val, WORD_SZ);
			data += WORD_SZ;
			currsize += WORD_SZ;
		} else {
			/* copy only remaining bytes */
			memcpy(data, &val, max - currsize);
			break;
		}
	} while (currsize < max);

	return currsize;
}