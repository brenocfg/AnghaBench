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
struct r820t_priv {int dummy; } ;

/* Variables and functions */
 int r820t_write (struct r820t_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int r820t_write_reg(struct r820t_priv *priv, u8 reg, u8 val)
{
	u8 tmp = val; /* work around GCC PR81715 with asan-stack=1 */

	return r820t_write(priv, reg, &tmp, 1);
}