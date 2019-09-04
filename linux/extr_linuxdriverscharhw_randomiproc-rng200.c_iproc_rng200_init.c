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
typedef  int /*<<< orphan*/  uint32_t ;
struct iproc_rng200_dev {scalar_t__ base; } ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 scalar_t__ RNG_CTRL_OFFSET ; 
 int /*<<< orphan*/  RNG_CTRL_RNG_RBGEN_ENABLE ; 
 int /*<<< orphan*/  RNG_CTRL_RNG_RBGEN_MASK ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct iproc_rng200_dev* to_rng_priv (struct hwrng*) ; 

__attribute__((used)) static int iproc_rng200_init(struct hwrng *rng)
{
	struct iproc_rng200_dev *priv = to_rng_priv(rng);
	uint32_t val;

	/* Setup RNG. */
	val = ioread32(priv->base + RNG_CTRL_OFFSET);
	val &= ~RNG_CTRL_RNG_RBGEN_MASK;
	val |= RNG_CTRL_RNG_RBGEN_ENABLE;
	iowrite32(val, priv->base + RNG_CTRL_OFFSET);

	return 0;
}