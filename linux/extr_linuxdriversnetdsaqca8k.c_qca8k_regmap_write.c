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
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qca8k_regmap_write(void *ctx, uint32_t reg, uint32_t val)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ctx;

	qca8k_write(priv, reg, val);

	return 0;
}