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
struct sja1105_cgu_idiv {int /*<<< orphan*/  pd; int /*<<< orphan*/  idiv; int /*<<< orphan*/  autoblock; int /*<<< orphan*/  clksrc; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void sja1105_cgu_idiv_packing(void *buf, struct sja1105_cgu_idiv *idiv,
				     enum packing_op op)
{
	const int size = 4;

	sja1105_packing(buf, &idiv->clksrc,    28, 24, size, op);
	sja1105_packing(buf, &idiv->autoblock, 11, 11, size, op);
	sja1105_packing(buf, &idiv->idiv,       5,  2, size, op);
	sja1105_packing(buf, &idiv->pd,         0,  0, size, op);
}