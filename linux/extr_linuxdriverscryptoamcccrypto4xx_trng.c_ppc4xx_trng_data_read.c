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
typedef  int /*<<< orphan*/  u32 ;
struct hwrng {scalar_t__ priv; } ;
struct crypto4xx_device {scalar_t__ trng_base; } ;

/* Variables and functions */
 scalar_t__ PPC4XX_TRNG_DATA ; 
 int /*<<< orphan*/  in_le32 (scalar_t__) ; 

__attribute__((used)) static int ppc4xx_trng_data_read(struct hwrng *rng, u32 *data)
{
	struct crypto4xx_device *dev = (void *)rng->priv;
	*data = in_le32(dev->trng_base + PPC4XX_TRNG_DATA);
	return 4;
}